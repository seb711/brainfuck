//
// Created by kosakseb on 22.10.23.
//

#ifndef HW1_VM_HPP
#define HW1_VM_HPP

#include <cstdint>
#include <vector>

namespace brainfuck {
    const size_t MEMORY_SIZE = 140000;

    class VM {
    public:
        // program is the pointer to instructions; size is the number of instructions
        explicit VM(int* program, int size) : instructions(program) {
        }

        void run();

    private:
        int* instructions;
        std::vector<uint8_t> memory;
    };
}




#endif //HW1_VM_HPP
