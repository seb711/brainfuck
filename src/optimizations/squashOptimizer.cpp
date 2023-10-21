//
// Created by kosakseb on 21.10.23.
//

#include "squashOptimizer.hpp"

namespace brainfuck {
    void SquashArithmeticOptimizationStep::optimize(NodeInstruction& root) {
        std::vector<NodeInstruction>& ins = root.childrenInstructions;
        std::vector<NodeInstruction> optIns{};

        bool squash = false;
        int diff;

        for (auto& i: ins) {
            if (i.kind == OptimizerOperation::OP_ADD || i.kind == OptimizerOperation::OP_SUB) {
                if (!squash) {
                    diff = 0;
                    squash = true;
                }

                diff += i.kind == OptimizerOperation::OP_ADD ? 1 : -1;
                continue;
            } else if (squash) {
                /// SQUASH INSTRUCTIONS
                squash = false;
                if (diff) {
                    NodeInstruction squashIns;
                    if (diff > 0) {
                        squashIns = NodeInstruction{.kind=OptimizerOperation::OP_ADD, .argument=diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
                    } else {
                        squashIns = NodeInstruction{.kind=OptimizerOperation::OP_SUB, .argument=-diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
                    }
                    optIns.push_back(squashIns);
                }
            }

            if (i.kind == OptimizerOperation::OP_LOOP) {
                this->optimize(i);
            }

            optIns.push_back(i);
        }

        /// CHECK IN THE END IF ANY OPEN INSTRUCTIONS
        if (squash) {
            /// SQUASH INSTRUCTIONS
            if (diff) {
                NodeInstruction squashIns;
                if (diff > 0) {
                    squashIns = NodeInstruction{.kind=OptimizerOperation::OP_ADD, .argument=diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
                } else {
                    squashIns = NodeInstruction{.kind=OptimizerOperation::OP_SUB, .argument=-diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
                }
                optIns.push_back(squashIns);
            }
        }

        root.childrenInstructions = optIns;
        root.childrenCount = optIns.size();

        return;
    }

 void SquashMoveOptimizationStep::optimize(NodeInstruction& root) {
     std::vector<NodeInstruction>& ins = root.childrenInstructions;
     std::vector<NodeInstruction> optIns{};

     bool squash = false;
     int diff;

     for (auto& i: ins) {
         if (i.kind == OptimizerOperation::OP_MOVE_LEFT || i.kind == OptimizerOperation::OP_MOVE_RIGHT) {
             if (!squash) {
                 diff = 0;
                 squash = true;
             }

             diff += i.kind == OptimizerOperation::OP_MOVE_RIGHT ? 1 : -1;
             continue;
         } else if (squash) {
             /// SQUASH INSTRUCTIONS
             squash = false;
             if (diff) {
                 NodeInstruction squashIns;
                 if (diff > 0) {
                     squashIns = NodeInstruction{.kind=OptimizerOperation::OP_MOVE_RIGHT, .argument=diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
                 } else {
                     squashIns = NodeInstruction{.kind=OptimizerOperation::OP_MOVE_LEFT, .argument=-diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
                 }
                 optIns.push_back(squashIns);
             }
         }

         if (i.kind == OptimizerOperation::OP_LOOP) {
             this->optimize(i);
         }

         optIns.push_back(i);
     }

     /// CHECK IN THE END IF ANY OPEN INSTRUCTIONS
     if (squash) {
         /// SQUASH INSTRUCTIONS
         if (diff) {
             NodeInstruction squashIns;
             if (diff > 0) {
                 squashIns = NodeInstruction{.kind=OptimizerOperation::OP_MOVE_RIGHT, .argument=diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
             } else {
                 squashIns = NodeInstruction{.kind=OptimizerOperation::OP_MOVE_LEFT, .argument=-diff, .childrenCount=0, .childrenInstructions=std::vector<NodeInstruction>()};
             }
             optIns.push_back(squashIns);
         }
     }

     root.childrenInstructions = optIns;
     root.childrenCount = optIns.size();

     return;
    }
}
