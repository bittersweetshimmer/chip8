cmake_minimum_required(VERSION 3.16)

set(CHIP8_SOURCES
    src/main.cpp
    src/chip8/Chip8.cpp
    src/chip8/Instruction.cpp
    src/chip8/Program.cpp
    src/chip8/RNG.cpp
    src/chip8/Instructions/ADD.cpp
    src/chip8/Instructions/AND.cpp
    src/chip8/Instructions/CALL.cpp
    src/chip8/Instructions/CLS.cpp
    src/chip8/Instructions/DRW.cpp
    src/chip8/Instructions/JP.cpp
    src/chip8/Instructions/LD.cpp
    src/chip8/Instructions/OR.cpp
    src/chip8/Instructions/RET.cpp
    src/chip8/Instructions/RND.cpp
    src/chip8/Instructions/SE.cpp
    src/chip8/Instructions/SHL.cpp
    src/chip8/Instructions/SHR.cpp
    src/chip8/Instructions/SKNP.cpp
    src/chip8/Instructions/SKP.cpp
    src/chip8/Instructions/SNE.cpp
    src/chip8/Instructions/SUB.cpp
    src/chip8/Instructions/SUBN.cpp
    src/chip8/Instructions/XOR.cpp
    src/chip8/Instructions/SYS.cpp
    src/chip8/GUI/Window.cpp
)

set(ALOOMY_SOURCES
    src/aloomy/Context.cpp
    src/aloomy/Device.cpp
    src/aloomy/Objects/Buffer.cpp
    src/aloomy/Objects/Source.cpp
)

add_executable(chip8 ${CHIP8_SOURCES} ${ALOOMY_SOURCES})

if (WIN32)
    target_compile_definitions(chip8 PRIVATE NOMINMAX)
endif()

find_package(OpenAL REQUIRED)

target_include_directories(chip8 PUBLIC include/)
target_include_directories(chip8 PRIVATE ${OPENAL_INCLUDE_DIR})

target_link_directories(chip8 PRIVATE ${OPENAL_LIBRARY})

target_link_libraries(chip8 glfw)
target_link_libraries(chip8 gloomy)

if (WIN32)
    target_link_libraries(chip8 OpenAL32)
else()
    target_link_libraries(chip8 openal)
endif()

set_target_properties(chip8 PROPERTIES CXX_STANDARD 20)