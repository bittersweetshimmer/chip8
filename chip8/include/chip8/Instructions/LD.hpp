#pragma once
#include <variant>
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Aliases/Byte.hpp>
#include <chip8/Aliases/Address.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    6xkk - LD Vx, byte
    
    Set Vx = kk.

    The interpreter puts the value kk into register Vx.
    */
    struct LDbyte {
        chip8::GPRegister vx;
        chip8::Byte byte;
    };

    /*
    8xy0 - LD Vx, Vy

    Set Vx = Vy.

    Stores the value of register Vy in register Vx.
    */
    struct LDregister {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };

    /*
    Annn - LD I, addr

    Set I = nnn.

    The value of register I is set to nnn.
    */
    struct LDaddress {
        chip8::Address address;
    };

    /*
    Fx07 - LD Vx, DT

    Set Vx = delay timer value.

    The value of DT is placed into Vx.
    */
    struct LDgetDelay{
        chip8::GPRegister vx;
    };

    /*
    Fx0A - LD Vx, K
    
    Wait for a key press, store the value of the key in Vx.

    All execution stops until a key is pressed, then the value of that key is stored in Vx.
    */
    struct LDkeyPress {
        chip8::GPRegister vx;
    };

    /*
    Fx15 - LD DT, Vx

    Set delay timer = Vx.

    DT is set equal to the value of Vx.
    */
    struct LDsetDelay {
        chip8::GPRegister vx;
    };

    /*
    Fx18 - LD ST, Vx

    Set sound timer = Vx.

    ST is set equal to the value of Vx.
    */
    struct LDsetSound {
        chip8::GPRegister vx;
    };

    /*
    Fx29 - LD F, Vx

    Set I = location of sprite for digit Vx.

    The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
    */
    struct LDsprite {
        chip8::GPRegister vx;
    };

    /*
    Fx33 - LD B, Vx
    
    Store BCD representation of Vx in memory locations I, I+1, and I+2.

    The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
    */
    struct LDbcd {
        chip8::GPRegister vx;
    };

    /*
    Fx55 - LD [I], Vx

    Store registers V0 through Vx in memory starting at location I.

    The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
    */
    struct LDstore {
        chip8::GPRegister vx;
    };

    /*
    Fx65 - LD Vx, [I]

    Read registers V0 through Vx from memory starting at location I.

    The interpreter reads values from memory starting at location I into registers V0 through Vx.
    */
    struct LDread {
        chip8::GPRegister vx;
    };


    using LD = std::variant<
        LDregister,
        LDbyte,
        LDgetDelay,
        LDkeyPress,
        LDsetDelay,
        LDsetSound,
        LDsprite,
        LDbcd,
        LDstore,
        LDread,
        LDaddress
    >;
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::LDregister> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDregister&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDregister> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDregister&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDregister>;
        static auto encode(const chip8::instructions::LDregister&) -> chip8::InstructionCode;
    };




    
    template<>
    struct Display<chip8::instructions::LDbyte> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDbyte&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDbyte> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDbyte&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDbyte>;
        static auto encode(const chip8::instructions::LDbyte&) -> chip8::InstructionCode;
    };




    
    template<>
    struct Display<chip8::instructions::LDgetDelay> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDgetDelay&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDgetDelay> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDgetDelay&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDgetDelay>;
        static auto encode(const chip8::instructions::LDgetDelay&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDkeyPress> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDkeyPress&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDkeyPress> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDkeyPress&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDkeyPress>;
        static auto encode(const chip8::instructions::LDkeyPress&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDsetDelay> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDsetDelay&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDsetDelay> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDsetDelay&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDsetDelay>;
        static auto encode(const chip8::instructions::LDsetDelay&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDsetSound> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDsetSound&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDsetSound> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDsetSound&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDsetSound>;
        static auto encode(const chip8::instructions::LDsetSound&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDsprite> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDsprite&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDsprite> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDsprite&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDsprite>;
        static auto encode(const chip8::instructions::LDsprite&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDbcd> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDbcd&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDbcd> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDbcd&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDbcd>;
        static auto encode(const chip8::instructions::LDbcd&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDstore> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDstore&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDstore> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDstore&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDstore>;
        static auto encode(const chip8::instructions::LDstore&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDread> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDread&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDread> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDread&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDread>;
        static auto encode(const chip8::instructions::LDread&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LDaddress> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LDaddress&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LDaddress> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LDaddress&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDaddress>;
        static auto encode(const chip8::instructions::LDaddress&) -> chip8::InstructionCode;
    };





    template<>
    struct Display<chip8::instructions::LD> : chip8::traits::Impl {
        static auto display(const chip8::instructions::LD&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::LD> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::LD&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LD>;
        static auto encode(const chip8::instructions::LD&) -> chip8::InstructionCode;
    };
}