//
// Created by kosakseb on 20.10.23.
//
#include <iostream>
#include <vector>
#include "parser.hpp"
#include "asm.hpp"
#include "optimizer.hpp"
#include "optimizations/squashOptimizer.hpp"
#include "optimizations/patternOptimizer.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " [brainfuck code]" << " [path to export bytecode]"<< std::endl;
        return 1;
    }

    std::string prog(argv[1]);

    brainfuck::Parser parser{prog};

    // std::cout << "PARSED" << std::endl;

    brainfuck::Optimizer optimizer{parser.getRoot()};

    // optimizer.getRoot().print();

    // std::cout << "OPTIMIZED" << std::endl << std::endl;

    // Parse the program into AST
    brainfuck::SquashArithmeticOptimizationStep aO = brainfuck::SquashArithmeticOptimizationStep();
    brainfuck::SquashMoveOptimizationStep mO = brainfuck::SquashMoveOptimizationStep();
    brainfuck::LoopPatternOptimizationStep pO = brainfuck::LoopPatternOptimizationStep();
    std::vector<brainfuck::OptimizationStep*> opts{&aO, &mO, &pO};
    optimizer.optimize(opts);

    // optimizer.getRoot().print();

    // std::cout << "COMPILE" << std::endl;

    brainfuck::ByteCompiler byteCompiler{optimizer.getRoot()};
    byteCompiler.exportByteCode(argv[2]);

    return 0;
}
