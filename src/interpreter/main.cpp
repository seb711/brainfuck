//
// Created by kosakseb on 22.10.23.
//
#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
#include "vm.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage ./vm program.brainfuck\n";
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        std::cerr << std::strerror(errno);
        return 1;
    }
    struct stat file_info = {};
    int ret = fstat(fd, &file_info);
    if (ret < 0) {
        std::cerr << std::strerror(errno);
        return 1;
    }
    auto file_size = file_info.st_size;
    int* memory = (int *) mmap(nullptr, file_size, PROT_READ, MAP_SHARED, fd, 0);
    if (memory == MAP_FAILED) {
        std::cerr << std::strerror(errno);
        return 1;
    }

    brainfuck::VM vm(memory, file_size / sizeof(*memory));
    vm.run();

    if (munmap(memory, file_size) < 0 || close(fd)) {
        std::cerr << std::strerror(errno);
        return 1;
    }
}