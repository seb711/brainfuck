//
// Created by kosakseb on 20.10.23.
//
#include <iostream>
#include <vector>
#include "parser.hpp"
#include "optimizer.hpp"

void printProgram(std::vector <brainfuck::Instruction> ops) {
    int counter = 0;
    for (auto i: ops) {
        std::cout << std::to_string(counter++) << " : ";
        i.print();
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [brainfuck code]" << std::endl;
        return 1;
    }

    std::string prog(argv[1]);

    brainfuck::Parser parser{prog};

    std::cout << "PARSED" << std::endl;

    brainfuck::ByteCompiler byteCompiler{parser.getRoot()};
    // Parse the program into AST

    printProgram(byteCompiler.ops);

    return 0;
}
