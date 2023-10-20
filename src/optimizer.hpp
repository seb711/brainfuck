//
// Created by kosakseb on 20.10.23.
//

#ifndef BRAINFUCK_OPTIMIZER_HPP
#define BRAINFUCK_OPTIMIZER_HPP

#include <vector>
#include "parser.hpp"

namespace brainfuck {
    enum ByteOperation {
        // ARITHMETIC OPS
        OP_ADD,
        OP_SUB,
        OP_MUL,
        // PC
        OP_MOVE_RIGHT,
        OP_MOVE_LEFT,
        // CONTROL
        OP_JUMP_NEQ_ZERO,
        // IO
        OP_OUTPUT,
        OP_INPUT
    };

    struct Instruction {
        ByteOperation op;
        int argument;

        void print();
    };

    class Optimizer {
    public:
        virtual std::vector<int> optimize(std::vector<Instruction> byteCode);
    };

    class ByteCompiler {
    private:
        const Node root;
        std::vector<Instruction> compileAst(Node node, size_t offset);

    public:
        ByteCompiler(Node _root);
        ~ByteCompiler() = default;

        std::vector<Instruction> ops;

        std::vector<Instruction> optimizeByteCode(std::vector<Optimizer> optimizer);
        void exportByteCode();
    };
}



#endif //HW1_OPTIMIZER_HPP
