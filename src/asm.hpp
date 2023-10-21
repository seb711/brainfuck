//
// Created by kosakseb on 20.10.23.
//

#ifndef BRAINFUCK_BYTECOMPILER_HPP
#define BRAINFUCK_BYTECOMPILER_HPP

#include <vector>
#include "optimizer.hpp"
#include <iostream>

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

    struct ByteInstruction {
        ByteOperation op;
        int argument;

        void print();
    };

    class ByteCompiler {
    private:
        const NodeInstruction root;
        std::vector<ByteInstruction> compileAst(Node node, size_t offset);

    public:
        ByteCompiler(NodeInstruction _root);
        ~ByteCompiler() = default;

        std::vector<ByteInstruction> ops;

        void exportByteCode();
    };
}



#endif //BRAINFUCK_BYTECOMPILER_HPP
