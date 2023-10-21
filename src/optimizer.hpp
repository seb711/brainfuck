//
// Created by kosakseb on 21.10.23.
//

#ifndef HW1_OPTIMIZER_HPP
#define HW1_OPTIMIZER_HPP

#include "parser.hpp"
#include <vector>

namespace brainfuck {
    enum OptimizerOperation {
        OP_START,
        // ARITHMETIC OPS
        OP_ADD,
        OP_SUB,
        OP_MUL,
        // PC
        OP_MOVE_RIGHT,
        OP_MOVE_LEFT,
        // CONTROL
        OP_LOOP,
        // IO
        OP_OUTPUT,
        OP_INPUT
    };

    struct NodeInstruction {
        OptimizerOperation kind;
        int argument;
        size_t childrenCount;
        std::vector <NodeInstruction> childrenInstructions;
        void print();
    };

    class OptimizationStep {
    public:
        OptimizationStep() = default;
        ~OptimizationStep() = default;
        virtual void optimize(NodeInstruction& root) {};
    };

    class Optimizer {
    private:
        NodeInstruction rootInstruction;
        NodeInstruction compileAst(Node& node);

    public:
        Optimizer(Node& root);
        ~Optimizer() = default;
        void optimize(std::vector<OptimizationStep*> optimizers);
        NodeInstruction& getRoot() {
            return rootInstruction;
        };
    };
}



#endif //HW1_OPTIMIZER_HPP
