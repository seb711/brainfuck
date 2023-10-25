//
// Created by kosakseb on 20.10.23.
//
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "parser.hpp"
#include "asm.hpp"
#include "optimizer.hpp"
#include "optimizations/squashOptimizer.hpp"
#include "optimizations/patternOptimizer.hpp"

// Compare the compile-time and the run-time:
// The compile-time is in my case always not measurable (always 0ms); so pretty fast, but currently
// i don't have very sophisticated optimizations steps. Nevertheless the run-time is twice as fast
// with the most basic optimizations.

// bench.bf
//      - non-opt: 1433ms
//      - opt: 14ms

// easyopt.bf
//      - non-opt: 29144ms
//      - opt: 19929ms

// The optimizations are worth as soon as there are other operations than increment and decrement of
// the cell or the memory pointer.

// How can more advanced optimizations be implemented?
// The optimization i'm currently trying to implement are loop operations like multiply or bigger operations like
// copying data from one address to another. That are rather common operations that take a lot of operations in my
// implementation.
// These optimizations could be implemented by a pattern (regular expression) matching on the brainfuck code. And
// you would need multiple optimization steps that get executed more than once in a pipeline fashion. E.g. the optimizations
// that compresses multiple add/sub operations to one operation has to be executed after a Fold-Offset-Optimization.
// Other optimizations that are possible but need more implementation effort would be:
//      - I/O Operations: Minimize number of system calls for input and output operations and try to group them
//      - Symbolic Execution and Control Flow Analysis: Analyze the control flow to identify branches and loop conditions
//          that could be simplified
//      - Parallelization: Parallelize parts of a brainfuck program

std::string read_code(std::string file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        return "";
    }

    std::string file_content;
    std::string line;
    while (std::getline(file, line)) {
        file_content += line;
    }

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

    auto t1 = std::chrono::high_resolution_clock::now();
    // Parse program into AST
    brainfuck::Parser parser{prog};

    // Optimize the program into AST
    brainfuck::Optimizer optimizer{parser.getRoot()};
    brainfuck::SquashArithmeticOptimizationStep aO = brainfuck::SquashArithmeticOptimizationStep();
    brainfuck::SquashMoveOptimizationStep mO = brainfuck::SquashMoveOptimizationStep();
    brainfuck::LoopPatternOptimizationStep pO = brainfuck::LoopPatternOptimizationStep();
    std::vector<brainfuck::OptimizationStep*> opts{&aO, &mO, &pO};
    optimizer.optimize(opts);

    // Compile AST to ByteCode
    brainfuck::ByteCompiler byteCompiler{optimizer.getRoot()};
    byteCompiler.exportByteCode(argv[2]);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "Compilation took " << ms_int.count() << "ms" << std::endl;

    return 0;
}
