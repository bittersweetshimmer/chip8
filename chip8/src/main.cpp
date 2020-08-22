#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#include <chip8/Chip8.hpp>
#include <chip8/Instruction.hpp>
#include <chip8/GUI/Window.hpp>

constexpr auto CLOCK_RATE = 500.0;
constexpr auto TIMER_RATE = 60.0;

constexpr auto KEY_MAPPING = std::array<chip8::gui::io::Key, chip8::KEYBOARD_SIZE>{
    chip8::gui::io::Key::KEY_0, chip8::gui::io::Key::KEY_1,
    chip8::gui::io::Key::KEY_2, chip8::gui::io::Key::KEY_3,
    chip8::gui::io::Key::KEY_4, chip8::gui::io::Key::KEY_5,
    chip8::gui::io::Key::KEY_6, chip8::gui::io::Key::KEY_7,
    chip8::gui::io::Key::KEY_8, chip8::gui::io::Key::KEY_9,
    chip8::gui::io::Key::A,     chip8::gui::io::Key::B,
    chip8::gui::io::Key::C,     chip8::gui::io::Key::D,
    chip8::gui::io::Key::E,     chip8::gui::io::Key::F
};

using Vec2         = std::array<gloomy::Float, 2>;
using Position     = gloomy::Attribute<struct PositionTag, Vec2>;
using TextureCoord = gloomy::Attribute<struct TextureCoordTag, Vec2>;
using Attributes   = gloomy::Attributes<Position, TextureCoord>;
using Vertex       = gloomy::Vertex<Position, TextureCoord>;
using Index        = gloomy::U8;

constexpr auto VERTEX_SHADER = R"(
#version 330 core
layout(location = 0) in vec2 v_position;
layout(location = 1) in vec2 v_texcoord;

out vec2 f_texcoord;

void main() {
    gl_Position = vec4(v_position, 0.0, 1.0);

    f_texcoord = v_texcoord;
}
)";

constexpr auto FRAGMENT_SHADER = R"(
#version 330 core
out vec4 o_color;

in vec2 f_texcoord;

uniform sampler2D u_texture;

void main() {
    o_color = vec4(texture(u_texture, f_texcoord).r, texture(u_texture, f_texcoord).r, texture(u_texture, f_texcoord).r, 1.0);
}
)";

auto main(int argc, char* argv[]) -> int {
    srand(time(0));
    auto chip8 = chip8::initialize({ 0x12, 0x00 }, rand());

    auto window = chip8::gui::Window(960, 480, "CHIP-8");
    if (!window.init()) {
        std::cout << "Window creation failed." << std::endl;
        return EXIT_FAILURE;
    }

    const auto program = gloomy::make_ready<gloomy::Program>(
        gloomy::make_ready<gloomy::VertexShader>(VERTEX_SHADER),
        gloomy::make_ready<gloomy::FragmentShader>(FRAGMENT_SHADER)
    );

    const auto indices = std::array<Index, 6>{0, 1, 3, 1, 2, 3};
    const auto vertices = std::array<Vertex, 4>{
        Vertex{{-1.0f,  1.0f}, {0.0f, 0.0f}},
        Vertex{{ 1.0f,  1.0f}, {1.0f, 0.0f}},
        Vertex{{ 1.0f, -1.0f}, {1.0f, 1.0f}},
        Vertex{{-1.0f, -1.0f}, {0.0f, 1.0f}},
    };

    auto display_texture = gloomy::make_generated<gloomy::Texture2D>(chip8.display.data(), chip8::DISPLAY_SIZE, chip8::DISPLAY_WIDTH, chip8::DISPLAY_HEIGHT);
    display_texture.internal_format = gloomy::TextureInternalFormat::RED;
    display_texture.pixel_format = gloomy::PixelFormat::RED;
    display_texture.pixel_data_type = gloomy::PixelDataType::U8;

    gloomy::use([&] { display_texture.commit(); }, display_texture);

    const auto index_buffer = gloomy::make_ready<gloomy::IndexBuffer>(indices);
    const auto vertex_buffer = gloomy::make_ready<gloomy::VertexBuffer>(vertices);
    const auto vertex_array = gloomy::make_generated<gloomy::VertexArray>(Attributes::dynamic());

    gloomy::use([&] { vertex_array.commit(); }, vertex_array, vertex_buffer, index_buffer);

    auto timer = window.get_next_frame().current_time;
    auto clock = timer;

    while (window.is_open()) {
        const auto timeframe = window.get_next_frame();

        if ((timeframe.current_time - timer) > (1.0 / TIMER_RATE)) {
            if (chip8.delay_timer != 0)
                chip8.delay_timer -= 1;

            if (chip8.sound_timer != 0)
                chip8.sound_timer -= 1;

            timer -= timeframe.current_time;
        }

        std::size_t cycles = (timeframe.current_time - clock) / (1.0 / CLOCK_RATE);

        while (const auto eventopt = window.get_event()) {
			const auto& event = eventopt.value();

			if (const auto drop_event = std::get_if<chip8::gui::ev::DropFileEvent>(&event)) {
				if (drop_event->paths.size() != 0) {
                    auto maybe_bytecode = chip8::read_file(drop_event->paths[0]);

                    if (!maybe_bytecode.has_value()) {
                        std::cout << "Invalid input." << std::endl;
                    }
                    else {
                        chip8 = chip8::initialize(std::move(maybe_bytecode).value(), rand());
                    }
                }
			}
            else if (const auto resize_event = std::get_if<chip8::gui::ev::WindowResizeEvent>(&event)) {
				gloomy::gl::raw::viewport(0, 0, resize_event->width, resize_event->height);
			}
		}

        for (std::size_t i = 0u; i < cycles; ++i) {
            clock = timeframe.current_time;

            chip8.previous_keyboard = chip8.keyboard;
            for (std::size_t key = 0x0; key < chip8::KEYBOARD_SIZE; ++key) {
                chip8::set_key(chip8.keyboard, key, window.input_buffer.contains(KEY_MAPPING[key]));
            }

            const auto ic = chip8::fetch(chip8);
            const auto maybe_instruction = chip8::decode<chip8::Instruction>(ic);

            if (maybe_instruction.has_value()) {
                const auto& instruction = maybe_instruction.value();

                chip8::execute(instruction, chip8);

                std::cout << chip8::display(instruction) << std::endl;
            }
            else {
                std::cout << "Invalid opcode: 0x" << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << ic << std::endl;
                return EXIT_FAILURE;
            }
        }

		gloomy::gl::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
		gloomy::gl::clear(gloomy::BufferBit::COLOR);

        program.bind();
        program.uniform("u_texture").sampler(0);
        display_texture.bind_at_slot(0);
        display_texture.commit();

        vertex_array.bind();
        gloomy::draw_indexed<Index>(gloomy::PrimitiveKind::TRIANGLES, indices.size());

        window.display();
		window.poll_events();
    }

    return EXIT_SUCCESS;
}