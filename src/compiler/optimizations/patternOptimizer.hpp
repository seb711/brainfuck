//
// Created by kosakseb on 21.10.23.
//

#ifndef HW1_PATTERNOPTIMIZER_HPP
#define HW1_PATTERNOPTIMIZER_HPP

#include "../optimizer.hpp"

namespace brainfuck {
    class LoopPatternOptimizationStep : public OptimizationStep {
    private:
        static NodeInstruction rewriteLoopPattern(NodeInstruction& loopNode);

    public:
        LoopPatternOptimizationStep() = default;
        ~LoopPatternOptimizationStep() = default;
        void optimize(NodeInstruction& root) override;
    };
}


#endif //HW1_PATTERNOPTIMIZER_HPP
