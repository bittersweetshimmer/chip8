#include <chip8/Instruction.hpp>

auto chip8::traits::Display<chip8::Instruction>::display(const chip8::Instruction& instruction) -> std::string {
    return std::visit([](auto&& v) -> std::string { return chip8::display(v); }, instruction);
};

auto chip8::traits::Instruction<chip8::Instruction>::execute(const chip8::Instruction& instruction, chip8::Chip8& chip8) -> void {
    std::visit([&chip8](auto&& v) -> void { return chip8::execute(v, chip8); }, instruction);
};

auto chip8::traits::Instruction<chip8::Instruction>::decode(chip8::InstructionCode ic) -> std::optional<chip8::Instruction> {
    if      (auto add  = chip8::decode<chip8::instructions::ADD> (ic)) return chip8::Instruction( add.value());
    else if (auto and_ = chip8::decode<chip8::instructions::AND> (ic)) return chip8::Instruction(and_.value());
    else if (auto call = chip8::decode<chip8::instructions::CALL>(ic)) return chip8::Instruction(call.value());
    else if (auto cls  = chip8::decode<chip8::instructions::CLS> (ic)) return chip8::Instruction( cls.value());
    else if (auto drw  = chip8::decode<chip8::instructions::DRW> (ic)) return chip8::Instruction( drw.value());
    else if (auto jp   = chip8::decode<chip8::instructions::JP>  (ic)) return chip8::Instruction(  jp.value());
    else if (auto ld   = chip8::decode<chip8::instructions::LD>  (ic)) return chip8::Instruction(  ld.value());
    else if (auto or_  = chip8::decode<chip8::instructions::OR>  (ic)) return chip8::Instruction( or_.value());
    else if (auto ret  = chip8::decode<chip8::instructions::RET> (ic)) return chip8::Instruction( ret.value());
    else if (auto rnd  = chip8::decode<chip8::instructions::RND> (ic)) return chip8::Instruction( rnd.value());
    else if (auto se   = chip8::decode<chip8::instructions::SE>  (ic)) return chip8::Instruction(  se.value());
    else if (auto shl  = chip8::decode<chip8::instructions::SHL> (ic)) return chip8::Instruction( shl.value());
    else if (auto shr  = chip8::decode<chip8::instructions::SHR> (ic)) return chip8::Instruction( shr.value());
    else if (auto sknp = chip8::decode<chip8::instructions::SKNP>(ic)) return chip8::Instruction(sknp.value());
    else if (auto skp  = chip8::decode<chip8::instructions::SKP> (ic)) return chip8::Instruction( skp.value());
    else if (auto sne  = chip8::decode<chip8::instructions::SNE> (ic)) return chip8::Instruction( sne.value());
    else if (auto sub  = chip8::decode<chip8::instructions::SUB> (ic)) return chip8::Instruction( sub.value());
    else if (auto subn = chip8::decode<chip8::instructions::SUBN>(ic)) return chip8::Instruction(subn.value());
    else if (auto xor_ = chip8::decode<chip8::instructions::XOR> (ic)) return chip8::Instruction(xor_.value());
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::Instruction>::encode(const chip8::Instruction& instruction) -> chip8::InstructionCode {
    return std::visit([](auto&& v) -> chip8::InstructionCode { return chip8::encode(v); }, instruction);
};