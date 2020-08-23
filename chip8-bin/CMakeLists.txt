cmake_minimum_required(VERSION 3.16)

set(CHIP8_BIN_SOURCES
    src/main.cpp
    src/chip8/GUI/Window.cpp
)

set(ALOOMY_SOURCES
    src/aloomy/Context.cpp
    src/aloomy/Device.cpp
    src/aloomy/Objects/Buffer.cpp
    src/aloomy/Objects/Source.cpp
)

add_executable(chip8-bin ${CHIP8_BIN_SOURCES} ${ALOOMY_SOURCES})

if (WIN32)
    target_compile_definitions(chip8 PRIVATE NOMINMAX)
endif()

find_package(OpenAL REQUIRED)

target_include_directories(chip8-bin PUBLIC include/)
target_include_directories(chip8-bin PRIVATE ${OPENAL_INCLUDE_DIR})

target_link_directories(chip8-bin PRIVATE ${OPENAL_LIBRARY})

target_link_libraries(chip8-bin chip8)
target_link_libraries(chip8-bin glfw)
target_link_libraries(chip8-bin gloomy)

if (WIN32)
    target_link_libraries(chip8-bin OpenAL32)
else()
    target_link_libraries(chip8-bin openal)
endif()

set_target_properties(chip8-bin PROPERTIES CXX_STANDARD 20)