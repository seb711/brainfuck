//
// Created by kosakseb on 20.10.23.
//
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "parser.hpp"
#include "asm.hpp"
#include "optimizer.hpp"
#include "optimizations/squashOptimizer.hpp"
#include "optimizations/patternOptimizer.hpp"

std::string read_code(std::string file_path) {
    // Open the file
    std::ifstream file(file_path);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        return "";
    }

    // Read the file content into a string
    std::string file_content;
    std::string line;
    while (std::getline(file, line)) {
        file_content += line;
    }

    // Close the file
    file.close();

    file_content.erase(std::remove(file_content.begin(), file_content.end(), '\n'), file_content.cend());
    file_content.erase(std::remove(file_content.begin(), file_content.end(), ' '), file_content.cend());

    return file_content;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " [path to .bf file]" << " [path to export bytecode]"<< std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    std::string prog = read_code(file_path);

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

    int counter = 0;
    for (auto i : byteCompiler.ops) {
        std::cout << std::to_string(counter) << " : ";
        i.print();
    }

    byteCompiler.exportByteCode(argv[2]);

    return 0;
}
