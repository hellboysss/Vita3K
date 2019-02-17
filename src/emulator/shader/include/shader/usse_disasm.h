#pragma once

#include <shader/types.h>

#include <string>

// TODO: make LOG_RAW
#define LOG_DISASM(fmt_str, ...) std::cout << fmt::format(fmt_str, ##__VA_ARGS__) << std::endl

//translator
namespace shader {
namespace usse {
namespace disasm {

//
// Disasm helpers
//

const std::string &opcode_str(const USSE::Opcode &e);
const char *e_predicate_str(USSE::ExtPredicate p);
const char *s_predicate_str(USSE::ShortPredicate p);
const char *move_data_type_str(USSE::MoveDataType p);
std::string reg_to_str(USSE::RegisterBank bank, uint32_t reg_num);
std::string operand_to_str(USSE::Operand op, USSE::Imm4 write_mask, std::uint32_t shift = 0);

template <std::size_t s>
std::string swizzle_to_str(USSE::Swizzle<s> swizz, const USSE::Imm4 write_mask, const std::uint32_t shift = 0) {
    std::string swizzstr;

    for (std::size_t i = 0; i < s; i++) {
        if (write_mask & (1 << ((i + shift) % s))) {
            switch (swizz[(i + shift) % s]) {
                case USSE::SwizzleChannel::_X: {
                    swizzstr += "x";
                    break;
                }
                case USSE::SwizzleChannel::_Y: {
                    swizzstr += "y";
                    break;
                }
                case USSE::SwizzleChannel::_Z: {
                    swizzstr += "z";
                    break;
                }
                case USSE::SwizzleChannel::_W: {
                    swizzstr += "w";
                    break;
                }
                case USSE::SwizzleChannel::_0: {
                    swizzstr += "0";
                    break;
                }
                case USSE::SwizzleChannel::_H: {
                    swizzstr += "H";
                    break;
                }
                default: {
                    swizzstr += "?";
                    break;
                }
            }
        } else {
            // Not available
            swizzstr += "-";
        }
    }
    
    // Erase all - at the end
    while (!swizzstr.empty() && swizzstr.back() == '-')
        swizzstr.pop_back();

    return swizzstr;
}

} // namespace disasm
} // namespace usse
} // namespace shader
