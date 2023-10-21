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
        BOP_ADD,
        BOP_SUB,
        BOP_MUL,
        // PC
        BOP_MOVE_RIGHT,
        BOP_MOVE_LEFT,
        // CONTROL
        BOP_JUMP_NEQ_ZERO,
        // IO
        BOP_OUTPUT,
        BOP_INPUT
    };

    struct ByteInstruction {
        ByteOperation op;
        int argument;

        void print();
    };

    class ByteCompiler {
    private:
        const NodeInstruction& root;
        std::vector<ByteInstruction> compileAst(const NodeInstruction& node, size_t offset);

    public:
        ByteCompiler(NodeInstruction& _root);
        ~ByteCompiler() = default;

        std::vector<ByteInstruction> ops;

        void exportByteCode();
    };
}



#endif //BRAINFUCK_BYTECOMPILER_HPP
