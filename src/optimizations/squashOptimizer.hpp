//
// Created by kosakseb on 21.10.23.
//

#ifndef HW1_SQUASHOPTIMIZER_HPP
#define HW1_SQUASHOPTIMIZER_HPP

#include "../optimizer.hpp"
#include <iostream>

namespace brainfuck {
    class SquashArithmeticOptimizationStep : public OptimizationStep {
    private:

    public:
        SquashArithmeticOptimizationStep() = default;
        ~SquashArithmeticOptimizationStep() = default;
        void optimize(NodeInstruction& root) override;
    };

    class SquashMoveOptimizationStep : public OptimizationStep {
    private:

    public:
        SquashMoveOptimizationStep() = default;
        ~SquashMoveOptimizationStep() = default;
        void optimize(NodeInstruction& root) override;
    };
}


#endif //HW1_SQUASHOPTIMIZER_HPP
