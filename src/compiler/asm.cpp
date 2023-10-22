//
// Created by kosakseb on 20.10.23.
//

#include "asm.hpp"
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring>

namespace brainfuck {
    void ByteInstruction::print() {
        switch (op) {
            case ByteOperation::BOP_OUTPUT:
                std::cout << "OP_OUTPUT ";
                break;
            case ByteOperation::BOP_INPUT:
                std::cout << "OP_INPUT ";
                break;
            case ByteOperation::BOP_SUB:
                std::cout << "OP_SUB ";
                break;
            case ByteOperation::BOP_ADD:
                std::cout << "OP_ADD ";
                break;
            case ByteOperation::BOP_MOVE_RIGHT:
                std::cout << "OP_MOVE_RIGHT ";
                break;
            case ByteOperation::BOP_MOVE_LEFT:
                std::cout << "OP_MOVE_LEFT ";
                break;
            case ByteOperation::BOP_JUMP_NEQ_ZERO:
                std::cout << "OP_JUMP_NEQ_ZERO ";
                break;
            case ByteOperation::BOP_SET_ZERO:
                std::cout << "BOP_SET_ZERO ";
                break;
            case ByteOperation::BOP_FIND_NEXT_ZERO:
                std::cout << "BOP_FIND_NEXT_ZERO ";
                break;
            case ByteOperation::BOP_DONE:
                std::cout << "BOP_DONE ";
                break;
        }

        std::cout << std::to_string(argument) << std::endl;
    }

    std::vector<ByteInstruction> ByteCompiler::compileAst(const NodeInstruction& node, size_t offset = 0) {
        std::vector<ByteInstruction> instructions{};

        for (auto i: node.childrenInstructions) {
            switch (i.kind) {
                case OptimizerOperation::OP_OUTPUT:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_OUTPUT, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_INPUT:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_INPUT, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_MOVE_RIGHT:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_MOVE_RIGHT, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_MOVE_LEFT:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_MOVE_LEFT, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_ADD:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_ADD, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_SUB:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_SUB, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_SET_ZERO:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_SET_ZERO, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_FIND_NEXT_ZERO:
                    instructions.push_back(ByteInstruction{.op=ByteOperation::BOP_FIND_NEXT_ZERO, .argument=i.argument});
                    break;
                case OptimizerOperation::OP_LOOP: {
                    std::vector <ByteInstruction> loopByteInstructions = compileAst(i, offset + instructions.size());
                    loopByteInstructions.push_back(
                            ByteInstruction{.op=ByteOperation::BOP_JUMP_NEQ_ZERO, .argument=static_cast<int>(offset + instructions.size())});
                    instructions.insert(std::end(instructions), std::begin(loopByteInstructions),
                                        std::end(loopByteInstructions));
                    break;
                }
                default:
                    break;
            }
        }

        return instructions;
    }

    void ByteCompiler::exportByteCode(const char* path) {
        std::vector<int> result{};

        for (auto& i: ops) {
            result.push_back(i.op);
            result.push_back(i.argument);
        }

        // now let`s write
        int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
        auto size = result.size() * sizeof(result[0]);
        if (fd < 0 || ftruncate(fd, size)) {
            throw output_error();
        }
        void* memory = mmap(nullptr, size, PROT_WRITE, MAP_SHARED, fd, 0);
        if (memory == MAP_FAILED) {
            throw output_error();
        }
        std::memcpy(memory, &result[0], size);
        munmap(memory, size);
        close(fd);
    }


    ByteCompiler::ByteCompiler(NodeInstruction& _root): root(_root) {
        ops = compileAst(root);
        ops.push_back(ByteInstruction{.op=ByteOperation::BOP_DONE, .argument=0});
    }

}
