#include <chip8/GUI/Window.hpp>

chip8::gui::Window::Window(int width, int height, const std::string& title)
    : width(width), height(height), title(title), handle(nullptr, nullptr) {}

chip8::gui::Window::~Window() {
    if (this->init_success) glfwTerminate();
}

auto chip8::gui::Window::init() -> bool {
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	auto monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	HandlePtr window(glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr), glfwDestroyWindow);
	if (window == nullptr) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window.get());
	glfwSetWindowUserPointer(window.get(), this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(window.get(), [](GLFWwindow* window, int width, int height) {
		auto self = static_cast<chip8::gui::Window*>(glfwGetWindowUserPointer(window));

		chip8::gui::Event resize_event = chip8::gui::ev::WindowResizeEvent{ width, height };

		self->width = width;
		self->height = height;

		self->event_queue.push(resize_event);
	});


	glfwSetWindowFocusCallback(window.get(), [](GLFWwindow* window, int focused) {
		auto self = static_cast<chip8::gui::Window*>(glfwGetWindowUserPointer(window));

		self->focus = focused == 0 ? false : true;
	});

	glfwSetKeyCallback(window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto self = static_cast<chip8::gui::Window*>(glfwGetWindowUserPointer(window));

		const auto _key = chip8::gui::io::to_key(key);
		const auto _action = chip8::gui::io::to_action(action);

		chip8::gui::Event key_event = chip8::gui::ev::KeyEvent{_key, _action};

		if (_action == chip8::gui::io::Action::PRESS) {
			self->input_buffer.insert(_key);
		}
		else if (_action == chip8::gui::io::Action::RELEASE) {
			self->input_buffer.erase(_key);
		}

		self->event_queue.push(key_event);
	});

	glfwSetDropCallback(window.get(), [](GLFWwindow* window, int count, const char** paths) {
		auto self = static_cast<chip8::gui::Window*>(glfwGetWindowUserPointer(window));

		std::vector<std::filesystem::path> fs_paths;
		fs_paths.reserve(count);

		for (auto i = 0; i < count; ++i) {
			fs_paths.emplace_back(paths[i]);
		}

		chip8::gui::Event drop = chip8::gui::ev::DropFileEvent{ std::move(fs_paths) };

		self->event_queue.push(drop);
	});

	this->handle = std::move(window);

	uint64_t frequency = glfwGetTimerFrequency();
	uint64_t value = glfwGetTimerValue();

	auto current = static_cast<chip8::gui::Time>(value) / static_cast<chip8::gui::Time>(frequency);
	this->previous_time = current;
	this->init_success = true;

	return true;
}

chip8::gui::Window::Window(chip8::gui::Window&& other) :
	width(other.width),
	height(other.height),
	title(std::move(other.title)),
	handle(std::move(other.handle)),
	previous_time(std::move(other.previous_time)),
	init_success(other.init_success) {
        other.init_success = false;
    }

chip8::gui::Window& chip8::gui::Window::operator=(chip8::gui::Window&& other) {
	this->width = other.width;
	this->height = other.height;
	this->title = std::move(other.title);
	this->handle = std::move(other.handle);
	this->previous_time = other.previous_time;
	this->init_success = other.init_success;

    other.init_success = false;

	return *this;
}

auto chip8::gui::Window::is_open() -> bool {
	return this->handle != nullptr && !glfwWindowShouldClose(this->handle.get());
}

auto chip8::gui::Window::close() -> void {
	this->handle = nullptr;
}

auto chip8::gui::Window::poll_events() -> void {
	glfwPollEvents();
}

auto chip8::gui::Window::get_event() -> std::optional<chip8::gui::Event> {
    if (this->event_queue.empty()) return std::nullopt;
	else {
		auto event = this->event_queue.front();
		this->event_queue.pop();

		return std::make_optional(event);
	}
}

auto chip8::gui::Window::get_next_frame() -> chip8::gui::TimeFrame {
	uint64_t frequency = glfwGetTimerFrequency();
	uint64_t value = glfwGetTimerValue();

	auto current = static_cast<chip8::gui::Time>(value) / static_cast<chip8::gui::Time>(frequency);
	auto delta = current - this->previous_time;
	this->previous_time = current;

	return { this->previous_time, delta };
}

auto chip8::gui::Window::display() -> void {
    if (this->handle) glfwSwapBuffers(this->handle.get());
}