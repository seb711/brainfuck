//
// Created by kosakseb on 20.10.23.
//
#include <iostream>
#include <vector>
#include "parser.hpp"
#include "optimizer.hpp"
#include "optimizations/squashOptimizer.hpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [brainfuck code]" << std::endl;
        return 1;
    }

    std::string prog(argv[1]);

    brainfuck::Parser parser{prog};

    std::cout << "PARSED" << std::endl;

    brainfuck::Optimizer optimizer{parser.getRoot()};

    optimizer.getRoot().print();

    std::cout << "OPTIMIZED" << std::endl;

    // Parse the program into AST
    brainfuck::SquashArithmeticOptimizationStep aO = brainfuck::SquashArithmeticOptimizationStep();
    brainfuck::SquashMoveOptimizationStep mO = brainfuck::SquashMoveOptimizationStep();
    std::vector<brainfuck::OptimizationStep*> opts{&aO, &mO};
    optimizer.optimize(opts);

    optimizer.getRoot().print();

    return 0;
}
