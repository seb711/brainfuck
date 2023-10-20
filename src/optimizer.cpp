//
// Created by kosakseb on 20.10.23.
//

#include "optimizer.hpp"
#include <iostream>

namespace brainfuck {
    void Instruction::print() {
        switch (op) {
            case ByteOperation::OP_OUTPUT:
                std::cout << "OP_OUTPUT ";
                break;
            case ByteOperation::OP_INPUT:
                std::cout << "OP_INPUT ";
                break;
            case ByteOperation::OP_SUB:
                std::cout << "OP_SUB ";
                break;
            case ByteOperation::OP_ADD:
                std::cout << "OP_ADD ";
                break;
            case ByteOperation::OP_MOVE_RIGHT:
                std::cout << "OP_MOVE_RIGHT ";
                break;
            case ByteOperation::OP_MOVE_LEFT:
                std::cout << "OP_MOVE_LEFT ";
                break;
            case ByteOperation::OP_JUMP_NEQ_ZERO:
                std::cout << "OP_JUMP_NEQ_ZERO ";
                break;
            case ByteOperation::OP_MUL:
                std::cout << "OP_MUL ";
                break;
        }

        std::cout << std::to_string(argument) << std::endl;
    }

    std::vector<Instruction> ByteCompiler::compileAst(Node node, size_t offset = 0) {
        std::vector<Instruction> instructions{};

        /// FOR LABEL THINGS CHECK ROOT NODE

        for (auto i: node.childrenInstructions) {
            switch (i.kind) {
                case ParserOperation::OUT:
                    instructions.push_back(Instruction{.op=ByteOperation::OP_OUTPUT, .argument=0});
                    break;
                case ParserOperation::IN:
                    instructions.push_back(Instruction{.op=ByteOperation::OP_INPUT, .argument=0});
                    break;
                case ParserOperation::MOVE_R:
                    instructions.push_back(Instruction{.op=ByteOperation::OP_MOVE_RIGHT, .argument=1});
                    break;
                case ParserOperation::MOVE_L:
                    instructions.push_back(Instruction{.op=ByteOperation::OP_MOVE_LEFT, .argument=1});
                    break;
                case ParserOperation::ADD:
                    instructions.push_back(Instruction{.op=ByteOperation::OP_ADD, .argument=1});
                    break;
                case ParserOperation::SUB:
                    instructions.push_back(Instruction{.op=ByteOperation::OP_SUB, .argument=1});
                    break;
                case ParserOperation::LOOP: {
                    std::vector <Instruction> loopInstructions = compileAst(i, offset + instructions.size());
                    loopInstructions.push_back(
                            Instruction{.op=ByteOperation::OP_JUMP_NEQ_ZERO, .argument=static_cast<int>(offset + instructions.size())});
                    instructions.insert(std::end(instructions), std::begin(loopInstructions),
                                        std::end(loopInstructions));
                    break;
                }
                default:
                    break;
            }
        }

        return instructions;
    }


    ByteCompiler::ByteCompiler(Node _root): root(_root) {
        ops = compileAst(root);
    };
}
