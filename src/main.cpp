#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <chip8/Chip8.hpp>
#include <chip8/Program.hpp>
#include <chip8/sprites/characters.hpp>
#include <curses.h>

auto main(int argc, char* argv[]) -> int {
    if (argc != 2) {
        std::cout << "Invalid number of arguments." << std::endl;
        return EXIT_FAILURE;
    }

    auto maybe_bytecode = chip8::read_file(argv[1]);
    if (!maybe_bytecode.has_value()) {
        std::cout << "Invalid input." << std::endl;
        return EXIT_FAILURE;
    }

    srand(time(0));
    auto chip8 = chip8::Chip8{};
    chip8.rng.engine.seed(rand());
    chip8::load(chip8.memory, chip8::sprites::CHARACTERS, 0x000);
    chip8::load(chip8.memory, std::move(maybe_bytecode.value()), chip8::INITIAL_PROGRAM_COUNTER);

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    auto display_window = newwin(chip8::DISPLAY_HEIGHT + 2, chip8::DISPLAY_WIDTH + 2, 0x0, 0x0);
    auto debug_window = newwin(chip8::DISPLAY_HEIGHT + 2, 0x20, 0x0, chip8::DISPLAY_WIDTH + 2);

    constexpr auto CLOCK_RATE = 500.0;
    constexpr auto TIMER_RATE = 60.0;

    auto previous_timer = std::chrono::high_resolution_clock::now();
    auto previous_time = std::chrono::high_resolution_clock::now();

    while (true) {
        auto current_time = std::chrono::high_resolution_clock::now();

        if (std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(current_time - previous_timer).count() > (1000.0 / TIMER_RATE)) {
            if (chip8.delay_timer != 0)
                chip8.delay_timer -= 1;

            if (chip8.sound_timer > 0)
                chip8.sound_timer -= 1;

            previous_timer = current_time;
        }

        if (std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(current_time - previous_time).count() < (1000.0 / CLOCK_RATE)) {
            continue;
        }

        previous_time = current_time;

        const auto ic = chip8::fetch(chip8);
        const auto maybe_instruction = chip8::decode<chip8::Instruction>(ic);

        for (std::size_t i = 0u; i < 0x10; ++i) {
            //chip8.keyboard[i] = false;
        }

        int key = 0;
        while ((key = wgetch(stdscr)) != ERR) {
            switch (key) {
                case '0': {
                    chip8.keyboard[0x0] = true;
                    break;
                }
                case '1': {
                    chip8.keyboard[0x1] = true;
                    break;
                }
                case '2': {
                    chip8.keyboard[0x2] = true;
                    break;
                }
                case '3': {
                    chip8.keyboard[0x3] = true;
                    break;
                }
                case '4': {
                    chip8.keyboard[0x4] = true;
                    break;
                }
                case '5': {
                    chip8.keyboard[0x5] = true;
                    break;
                }
                case '6': {
                    chip8.keyboard[0x6] = true;
                    break;
                }
                case '7': {
                    chip8.keyboard[0x7] = true;
                    break;
                }
                case '8': {
                    chip8.keyboard[0x8] = true;
                    break;
                }
                case '9': {
                    chip8.keyboard[0x9] = true;
                    break;
                }
                case 'a': {
                    chip8.keyboard[0xA] = true;
                    break;
                }
                case 'b': {
                    chip8.keyboard[0xB] = true;
                    break;
                }
                case 'c': {
                    chip8.keyboard[0xC] = true;
                    break;
                }
                case 'd': {
                    chip8.keyboard[0xD] = true;
                    break;
                }
                case 'e': {
                    chip8.keyboard[0xE] = true;
                    break;
                }
                case 'f': {
                    chip8.keyboard[0xF] = true;
                    break;
                }
            }
        }
        
        { // DRAW DISPLAY
            for (std::size_t y = 0u; y < chip8::DISPLAY_HEIGHT; ++y) {
                for (std::size_t x = 0u; x < chip8::DISPLAY_WIDTH; ++x) {
                    mvwaddch(display_window, y + 1, x + 1, chip8.display[x + y * chip8::DISPLAY_WIDTH] != 0x00 ? (char)254u : ' ');
                }
            }

            wborder(display_window, 0, 0, 0, 0, 0, 0, 0, 0);
            wrefresh(display_window);
        }


        { // PC, IC, SP, I
            std::ostringstream ss;

            ss << "PC = 0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << chip8.program_counter;

            wmove(debug_window, 1 + 16 + 1, 1);
            waddstr(debug_window, ss.str().c_str());
            ss.str("");
            ss.clear();

            ss << "IC = 0x" << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << ic;
            if (maybe_instruction.has_value()) ss << " [" << std::setfill(' ') << std::setw(15) << chip8::display(maybe_instruction.value()) << "]";

            wmove(debug_window, 1 + 16 + 2, 1);
            waddstr(debug_window, ss.str().c_str());
            ss.str("");
            ss.clear();

            ss << "SP = 0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(chip8.stack_pointer);

            wmove(debug_window, 1 + 16 + 3, 1);
            waddstr(debug_window, ss.str().c_str());
            ss.str("");
            ss.clear();

            ss << "I = 0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << chip8.address_register;

            wmove(debug_window, 1 + 16 + 4, 1);
            waddstr(debug_window, ss.str().c_str());
            ss.str("");
            ss.clear();
        }

        { // STACK & REGISTERS
            for (std::size_t i = 0u; i < chip8::STACK_SIZE; ++i) {
                std::ostringstream ss;

                ss << "S";
                ss << std::uppercase << std::hex << static_cast<std::size_t>(i);
                ss << " = 0x";
                ss << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(chip8.stack[i]);
                ss << " ";

                std::string output = ss.str();

                wmove(debug_window, 1 + i, 12);
                waddstr(debug_window, output.c_str());
            }

            for (std::size_t i = 0u; i < chip8::GENERAL_PURPOSE_REGISTERS_SIZE; ++i) {
                std::ostringstream ss;

                ss << "V";
                ss << std::uppercase << std::hex << static_cast<std::size_t>(i);
                ss << " = 0x";
                ss << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(chip8.general_purpose_registers[i]);
                ss << " ";

                std::string output = ss.str();

                wmove(debug_window, 1 + i, 1);
                waddstr(debug_window, output.c_str());
            }

            for (std::size_t i = 0u; i < chip8::KEYBOARD_SIZE; ++i) {
                std::ostringstream ss;

                ss << "K";
                ss << std::uppercase << std::hex << static_cast<std::size_t>(i);
                ss << " = ";
                ss << std::boolalpha << static_cast<std::size_t>(chip8.keyboard[i]);
                ss << " ";

                std::string output = ss.str();

                wmove(debug_window, 1 + i, 24);
                waddstr(debug_window, output.c_str());
            }
        }

        wborder(debug_window, 0, 0, 0, 0, 0, 0, 0, 0);
        wrefresh(debug_window);
            
        if (maybe_instruction.has_value()) {
            chip8::execute(maybe_instruction.value(), chip8);
        }
        else {
            wmove(debug_window, chip8::DISPLAY_HEIGHT, 1);

            std::ostringstream ss;
            ss << "Invalid opcode: 0x" << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << ic;
            waddstr(debug_window, ss.str().c_str());
            ss.str("");
            ss.clear();

            wborder(debug_window, 0, 0, 0, 0, 0, 0, 0, 0);
            wrefresh(debug_window);
            
            getchar();
            break;
        }
    }

    delwin(debug_window);
    delwin(display_window);
    endwin();

    return 0;
}