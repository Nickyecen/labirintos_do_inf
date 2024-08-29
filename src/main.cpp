#include <iostream>
#include <filesystem>
#include <unistd.h>

#include "include/stateMachine.hpp"

int main(int argc, char* argv[]) { 

    std::filesystem::path exe = std::filesystem::canonical(argv[0]);
    std::filesystem::path dir = exe.parent_path();

    if (!chdir(dir.c_str())) {
        std::clog << "Changed working directory to: " << dir << std::endl;
    } else {
        std::cerr << "Failed to change working directory to: " << dir << std::endl;
    } 

    StateMachine::run(); 
}
