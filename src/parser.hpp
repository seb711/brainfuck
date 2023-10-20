#ifndef BRAINFUCK_INTERPRETER_HPP
#define BRAINFUCK_INTERPRETER_HPP

#include <vector>
#include <string>
#include <memory>

enum Operation {
    ADD,
    SUB,
    IN,
    OUT,
    MOVE_R,
    MOVE_L,
    LOOP,
    NOOP,
    PROC
};

struct Node {
    Operation kind;
    size_t childrenCount;
    std::vector<Node> childrenInstructions;
};

class Parser {
private:
    const std::string program;
    Node root;

    unsigned pc = 0;
    unsigned rec = 0;

    Node compileProcedure();


public:
    Parser(std::string _program);
    ~Parser() = default;

    Node getRoot();
};

class syntax_error
        : public std::exception {
public:
    [[nodiscard]] const char *what() const

    noexcept override{
            return "syntax is not correct";
    }
};

#endif //BRAINFUCK_INTERPRETER_HPP
