//
// Created by kosakseb on 21.10.23.
//

#include "patternOptimizer.hpp"
#include <iostream>

namespace brainfuck {
    NodeInstruction LoopPatternOptimizationStep::rewriteLoopPattern(NodeInstruction& loopNode) {
        /// CHECK SINGLE LOOP INS
        if (loopNode.childrenCount == 1) {
            NodeInstruction& loopBody = loopNode.childrenInstructions[0];
            switch (loopBody.kind) {
                case OptimizerOperation::OP_SUB: {
                    return loopBody.argument == 1 ? NodeInstruction{.kind=OptimizerOperation::OP_SET_ZERO, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()} : loopNode;
                }
                case OptimizerOperation::OP_MOVE_RIGHT: {
                    return loopBody.argument == 1 ? NodeInstruction{.kind=OptimizerOperation::OP_FIND_NEXT_ZERO, .argument=1, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()} : loopNode;
                }
                default:
                    break;
            }
        }
        return loopNode;
    }

    void LoopPatternOptimizationStep::optimize(NodeInstruction &root) {
        for (auto &i: root.childrenInstructions) {
            if (i.kind == OptimizerOperation::OP_LOOP) {
                NodeInstruction newLoop = LoopPatternOptimizationStep::rewriteLoopPattern(i);
                if (newLoop.kind != OptimizerOperation::OP_LOOP) {
                    i.kind = newLoop.kind;
                    i.argument = newLoop.argument;
                    i.childrenInstructions = newLoop.childrenInstructions;
                    i.childrenCount = newLoop.childrenCount;
                } else {
                    this->optimize(i);
                }
            }
        }
    }
}