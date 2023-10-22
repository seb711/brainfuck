//
// Created by kosakseb on 22.10.23.
//

#include "vm.hpp"
#include "../compiler/asm.hpp"

namespace brainfuck {
    void VM::run() {
        memory = std::vector<uint8_t>(MEMORY_SIZE, 0);
        uint32_t memoryPtr = 0;
        uint32_t instructionPtr = 0;

        while (true) {
            instructionPtr++;

            // std::cout << "IP: " << std::to_string(instructionPtr) << std::endl;
            // std::cout << "MP: " << std::to_string(memoryPtr)<< " "  << std::to_string(memory[memoryPtr]) << std::endl;

            switch (static_cast<ByteOperation>(instructions[instructionPtr - 1])) {
                case ByteOperation::BOP_ADD: {
                    // std::cout << "BOP_ADD " << std::to_string(instructions[instructionPtr]) << std::endl;
                    auto arg = instructions[instructionPtr];
                    this->memory[memoryPtr] += static_cast<int8_t>(arg);
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_SUB: {
                    // std::cout << "BOP_SUB " << std::to_string(instructions[instructionPtr]) << std::endl;
                    auto arg = instructions[instructionPtr];
                    this->memory[memoryPtr] -= static_cast<int8_t>(arg);
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_MOVE_RIGHT: {
                    // std::cout << "BOP_MOVE_RIGHT " << std::to_string(instructions[instructionPtr]) << std::endl;
                    auto arg = instructions[instructionPtr];
                    memoryPtr += arg;
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_MOVE_LEFT: {
                    // std::cout << "BOP_MOVE_LEFT " << std::to_string(instructions[instructionPtr]) << std::endl;
                    auto arg = instructions[instructionPtr];
                    memoryPtr -= arg;
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_JUMP_NEQ_ZERO: {
                    // std::cout << "BOP_JUMP_NEQ_ZERO " << std::to_string(instructions[instructionPtr]) << std::endl;
                    if (this->memory[memoryPtr] != 0) {
                        auto arg = instructions[instructionPtr];
                        instructionPtr = arg * 2;
                    } else {
                        instructionPtr++;
                    }
                    break;
                }
                case ByteOperation::BOP_OUTPUT: {
                    // std::cout << "BOP_OUTPUT " << std::to_string(instructions[instructionPtr]) << std::endl;
                    std::cout << this->memory[memoryPtr];
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_INPUT: {
                    // std::cout << "BOP_INPUT " << std::to_string(instructions[instructionPtr]) << std::endl;
                    std::cin >> this->memory[memoryPtr];
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_SET_ZERO: {
                    // std::cout << "BOP_SET_ZERO " << std::to_string(instructions[instructionPtr]) << std::endl;
                    this->memory[memoryPtr] = 0;
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_FIND_NEXT_ZERO: {
                    // std::cout << "BOP_FIND_NEXT_ZERO " << std::to_string(instructions[instructionPtr]) << std::endl;
                    do {
                        memoryPtr++;
                    } while (!this->memory[memoryPtr]);
                    instructionPtr++;
                    break;
                }
                case ByteOperation::BOP_DONE: {
                    // std::cout << "BOP_DONE " << std::to_string(instructions[instructionPtr]) << std::endl;
                    std::cout << "DONE" << std::endl;
                    return;
                }
                default:
                    std::cout << "ERROR" << std::endl;
                    return;
            }
        }
    }
}