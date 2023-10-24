//
// Created by kosakseb on 22.10.23.
//

#include "vm.hpp"
#include "../compiler/asm.hpp"

namespace brainfuck {
    void VM::run() {
        size_t pc = 0;
        static const void* table[] = {
                &&CASE_ADD,
                &&CASE_SUB,
                &&CASE_MOVE_RIGHT,
                &&CASE_MOVE_LEFT,
                &&CASE_JUMP_NEQZ,
                &&CASE_OUTPUT,
                &&CASE_INPUT,
                &&CASE_SET_ZERO,
                &&CASE_FIND_NEXT_ZERO,
                &&CASE_DONE};

#define DISPATCH do { goto *table[static_cast<size_t>(instructions[pc++].op)]; } while (0)

                CASE_ADD: {
                    s.arr[s.ptr] += static_cast<uint8_t>(instructions[pc - 1].data);
                    DISPATCH;
                }
                CASE_SUB: {
                    s.arr[s.ptr] -= static_cast<uint8_t>(instructions[pc - 1].data);
                    DISPATCH;
                }
                CASE_MOVE_RIGHT: {
                    s.ptr += static_cast<uint8_t>(instructions[pc - 1].data);
                    DISPATCH;
                }
                CASE_MOVE_LEFT: {
                    s.ptr -= static_cast<uint8_t>(instructions[pc - 1].data);
                    DISPATCH;
                }
                CASE_JUMP_NEQZ: {
                    if (s.arr[s.ptr]) {
                        pc = instructions[pc - 1].data;
                    }
                    DISPATCH;
                }
                CASE_OUTPUT: {
                    std::cout << s.arr[s.ptr];
                    DISPATCH;
                }
                CASE_INPUT: {
                    std::cin >> s.arr[s.ptr];
                    DISPATCH;
                }
                CASE_SET_ZERO: {
                    s.arr[s.ptr] = 0;
                    DISPATCH;
                }
                CASE_FIND_NEXT_ZERO: while (s.arr[s.ptr] != '\0') {s.ptr++;}; DISPATCH;
                CASE_DONE: {
                    std::cout << std::endl << "DONE" << std::endl;
                    return;
                }
    }
}