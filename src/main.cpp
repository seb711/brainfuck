//
// Created by kosakseb on 20.10.23.
//
#include <iostream>
#include <vector>
#include "parser.hpp"

void printProgram(Node prog) {
    for (auto i : prog.childrenInstructions) {
        switch (i.kind) {
            case Operation::OUT:
                std::cout << "OUT" << std::endl;
                break;
            case Operation::IN:
                std::cout << "IN" << std::endl;
                break;
            case Operation::MOVE_R:
                std::cout << "MOVE_R" << std::endl;
                break;
            case Operation::MOVE_L:
                std::cout << "MOVE_L" << std::endl;
                break;
            case Operation::ADD:
                std::cout << "ADD" << std::endl;
                break;
            case Operation::SUB:
                std::cout << "SUB" << std::endl;
                break;
            case Operation::LOOP:
                std::cout << "LOOP" << std::endl;
                printProgram(i);
                std::cout << "LOOP END" << std::endl;
                break;
            case Operation::NOOP:
                std::cout << "NOOP" << std::endl;
                break;
            case Operation::PROC:
                std::cout << "PROC" << std::endl;
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [brainfuck code]" << std::endl;
        return 1;
    }

    std::string prog(argv[1]);

    Parser parser{prog};

    // Parse the program into AST

    printProgram(parser.getRoot());

    return 0;
}

