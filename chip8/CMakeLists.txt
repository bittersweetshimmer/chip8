cmake_minimum_required(VERSION 3.16)

set(CHIP8_SOURCES
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
)

add_library(chip8 ${CHIP8_SOURCES})

if (WIN32)
    target_compile_definitions(chip8 PRIVATE NOMINMAX)
endif()

target_include_directories(chip8 PUBLIC include/)
set_target_properties(chip8 PROPERTIES CXX_STANDARD 20)