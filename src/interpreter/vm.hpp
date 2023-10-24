//
// Created by kosakseb on 22.10.23.
//

#ifndef HW1_VM_HPP
#define HW1_VM_HPP

#include <cstdint>
#include <vector>
#include <stddef.h>

namespace brainfuck {
    const size_t MEMORY_SIZE = 140000;

    struct op { int op; int data; };
    struct state { std::vector<uint8_t> arr; size_t ptr; };

    class VM {
    public:
        // program is the pointer to instructions; size is the number of instructions
        explicit VM(int* program, int size) : instructions(std::vector<op>(reinterpret_cast<op*>(program), reinterpret_cast<op*>(program) + size)), s({.arr=std::vector<uint8_t>(MEMORY_SIZE, 0), .ptr=0}) {
        }

        void run();

    private:
        std::vector<struct op> instructions;
        struct state s;
    };
}




#endif //HW1_VM_HPP
