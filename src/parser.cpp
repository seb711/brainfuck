//
// Created by kosakseb on 20.10.23.
//
#include "parser.hpp"

namespace brainfuck {
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
                    ins.push_back(Node {.kind = ParserOperation::OUT, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                    break;
                case ',':
                    ins.push_back(Node{.kind = ParserOperation::IN, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                    break;
                case '>':
                    ins.push_back(Node{.kind = ParserOperation::MOVE_R, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                    break;
                case '<':
                    ins.push_back(Node{.kind = ParserOperation::MOVE_L, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                    break;
                case '+':
                    ins.push_back(Node{.kind = ParserOperation::ADD, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                    break;
                case '-':
                    ins.push_back(Node{.kind = ParserOperation::SUB, .childrenCount = 0, .childrenInstructions = std::vector<Node>()});
                    break;
                case '[': {
                    this->rec++;
                    Node loopNode = this->compileProcedure();
                    if (loopNode.kind == ParserOperation::LOOP) {
                        ins.push_back(loopNode);
                    }
                    break;
                }
                case ']': {
                    if (rec < 1) {
                        throw syntax_error();
                    }
                    this->rec--;

                    /// SHOULD I ADD HERE THE OPTIMIZATIONS?
                    /// OR IMPLEMENT OWN OPTIMIZATION STEP

                    return Node{.kind=ParserOperation::LOOP, .childrenCount=ins.size(), .childrenInstructions=ins};
                }
                default:
                    throw syntax_error();
            }

        if (rec > 0) {
            this->rec--;
            return Node{.kind=ParserOperation::NOOP, .childrenCount=0, .childrenInstructions=std::vector<Node>()};
        }

        return {.kind=ParserOperation::PROC, .childrenCount=ins.size(), .childrenInstructions=ins};
    }
}



