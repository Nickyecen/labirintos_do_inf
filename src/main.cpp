#include <iostream>
#include <filesystem>
#include <raylib.h>
#include <unistd.h>

#include "include/stateMachine.hpp"

int main(int argc, char* argv[]) { 

    std::filesystem::path exe = std::filesystem::canonical(argv[0]);
    std::filesystem::path dir = exe.parent_path();

    if (!chdir(dir.c_str())) {
        std::clog << "LOG: Changed working directory to: " << dir << std::endl;
    } else {
        std::cerr << "ERROR: Failed to change working directory to: " << dir << std::endl;
    }

    StateMachine::run(); 
}
