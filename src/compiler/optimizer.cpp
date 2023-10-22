//
// Created by kosakseb on 21.10.23.
//

#include "optimizer.hpp"
#include <iostream>

namespace brainfuck {
    void NodeInstruction::print() {
        switch (kind) {
            case OptimizerOperation::OP_START:
                std::cout << "OP_START " << std::endl;
                for (auto i : this->childrenInstructions) {
                    i.print();
                }
                std::cout << "OP_END ";
                break;
            case OptimizerOperation::OP_OUTPUT:
                std::cout << "OP_OUTPUT ";
                break;
            case OptimizerOperation::OP_INPUT:
                std::cout << "OP_INPUT ";
                break;
            case OptimizerOperation::OP_SUB:
                std::cout << "OP_SUB ";
                break;
            case OptimizerOperation::OP_ADD:
                std::cout << "OP_ADD ";
                break;
            case OptimizerOperation::OP_MOVE_RIGHT:
                std::cout << "OP_MOVE_RIGHT ";
                break;
            case OptimizerOperation::OP_MOVE_LEFT:
                std::cout << "OP_MOVE_LEFT ";
                break;
            case OptimizerOperation::OP_LOOP:
                std::cout << "OP_LOOP " << std::endl;
                for (auto i : this->childrenInstructions) {
                    i.print();
                }
                std::cout << "OP_LOOP_END ";
                break;
            case OptimizerOperation::OP_MUL:
                std::cout << "OP_MUL ";
                break;
            case OptimizerOperation::OP_SET_ZERO:
                std::cout << "OP_SET_ZERO ";
                break;
            case OptimizerOperation::OP_FIND_NEXT_ZERO:
                std::cout << "OP_FIND_NEXT_ZERO ";
                break;
        }

        std::cout << std::to_string(argument) << std::endl;
    }

    NodeInstruction Optimizer::compileAst(Node &node) {
        switch (node.kind) {
            case ParserOperation::OUT:
                return NodeInstruction{.kind=OptimizerOperation::OP_OUTPUT, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
            case ParserOperation::IN:
                return NodeInstruction{.kind=OptimizerOperation::OP_INPUT, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
            case ParserOperation::MOVE_R:
                return NodeInstruction{.kind=OptimizerOperation::OP_MOVE_RIGHT, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
            case ParserOperation::MOVE_L:
                return NodeInstruction{.kind=OptimizerOperation::OP_MOVE_LEFT, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
            case ParserOperation::ADD:
                return NodeInstruction{.kind=OptimizerOperation::OP_ADD, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
            case ParserOperation::SUB:
                return NodeInstruction{.kind=OptimizerOperation::OP_SUB, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
            case ParserOperation::LOOP: {
                std::vector <NodeInstruction> childrenInstructions{};
                for (auto ins: node.childrenInstructions) {
                    childrenInstructions.push_back(this->compileAst(ins));
                }
                return NodeInstruction{.kind=OptimizerOperation::OP_LOOP, .argument=0, .childrenCount=childrenInstructions.size(), .childrenInstructions=childrenInstructions};
            }
            case ParserOperation::PROC: {
                std::vector <NodeInstruction> childrenInstructions{};
                for (auto ins: node.childrenInstructions) {
                    childrenInstructions.push_back(this->compileAst(ins));
                }
                return NodeInstruction{.kind=OptimizerOperation::OP_START, .argument=0, .childrenCount=childrenInstructions.size(), .childrenInstructions=childrenInstructions};
            }
            default:
                return NodeInstruction{.kind=OptimizerOperation::OP_ADD, .argument=0, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
        }
    }

    Optimizer::Optimizer(Node &root) {
        rootInstruction = compileAst(root);
    }

    void Optimizer::optimize(std::vector<OptimizationStep *> optimizers) {
        for (auto i: optimizers) {
            i->optimize(rootInstruction);
        }
    }
}