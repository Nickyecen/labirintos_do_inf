#include "include/map.hpp"
#include <fstream>
#include <string>

// ############ MAP ############
Map::Map(std::string path) {
    std::ifstream file(path);

    if(!file.is_open()) {
        std::cerr<<"ERROR: Error while opening map: "<<path<<'\n';
    }

    if(!(file>>rows>>cols)) {
        std::cerr<<"ERROR: Error while reading size of map: "<<path<<'\n';
    }

    this->charMap = new char*[rows];

    std::string line;
    std::getline(file, line);
    for(int row = 0; row < rows; row++) {

        if(std::getline(file, line)) { 

            charMap[row] = new char[cols];
            for(int col = 0; col < cols; col++)
                charMap[row][col] = line[col];

        } else {
            std::cerr<<"ERROR: Error while reading map: "<<path<<'\n';
        }

    }

}

void Map::print() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            std::cout<<charMap[i][j];
        std::cout<<'\n';
    }
}
