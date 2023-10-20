//
// Created by kosakseb on 20.10.23.
//
#include "parser.hpp"

Parser::Parser(std::string _program): program(_program) {
    this->rec = 0;
    this->pc = 0;

    root = this->compileProcedure();
}

Node Parser::getRoot() {
    return this->root;
}

Node Parser::compileProcedure() {
    std::vector<Node> ins{};
    while (this->program[pc])
        switch (this->program[pc++]) {
            case '.':
                ins.push_back(Node {.kind = Operation::OUT, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                break;
            case ',':
                ins.push_back(Node{.kind = Operation::IN, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                break;
            case '>':
                ins.push_back(Node{.kind = Operation::MOVE_R, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                break;
            case '<':
                ins.push_back(Node{.kind = Operation::MOVE_L, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                break;
            case '+':
                ins.push_back(Node{.kind = Operation::ADD, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                break;
            case '-':
                ins.push_back(Node{.kind = Operation::SUB, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                break;
            case '[': {
                this->rec++;
                ins.push_back(this->compileProcedure());
                break;
            }
            case ']': {
                if (rec < 1) {
                    throw syntax_error();
                }
                this->rec--;
                return Node{.kind=Operation::LOOP, .childrenCount=ins.size(), .childrenInstructions=ins};
            }
        }

    if (rec > 0) {
        return Node{.kind=Operation::NOOP, .childrenCount=0, .childrenInstructions=std::vector<Node>()};
    }

    return {.kind=Operation::PROC, .childrenCount=ins.size(), .childrenInstructions=ins};
}


