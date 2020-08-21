cmake_minimum_required(VERSION 3.18.1)

project(chip8 VERSION 0.1.0 LANGUAGES CXX)

set(SOURCES
    src/main.cpp
    src/chip8/Chip8.cpp
    src/chip8/Instruction.cpp
    src/chip8/Program.cpp
    src/chip8/RNG.cpp
    src/chip8/instructions/ADD.cpp
    src/chip8/instructions/AND.cpp
    src/chip8/instructions/CALL.cpp
    src/chip8/instructions/CLS.cpp
    src/chip8/instructions/DRW.cpp
    src/chip8/instructions/JP.cpp
    src/chip8/instructions/LD.cpp
    src/chip8/instructions/OR.cpp
    src/chip8/instructions/RET.cpp
    src/chip8/instructions/RND.cpp
    src/chip8/instructions/SE.cpp
    src/chip8/instructions/SHL.cpp
    src/chip8/instructions/SHR.cpp
    src/chip8/instructions/SKNP.cpp
    src/chip8/instructions/SKP.cpp
    src/chip8/instructions/SNE.cpp
    src/chip8/instructions/SUB.cpp
    src/chip8/instructions/SUBN.cpp
    src/chip8/instructions/XOR.cpp
)

add_executable(chip8 ${SOURCES})

target_include_directories(chip8 PUBLIC include/)
target_include_directories(chip8 PRIVATE /usr/include/)

target_link_libraries(chip8 ncurses)

set_target_properties(chip8 PROPERTIES CXX_STANDARD 20)