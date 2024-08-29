#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <iostream>

class Map {

    // VARIABLES
    private:
        int rows, cols;
        char** charMap;

    // METHODS
    public:
        Map(std::string path);
        void print();

};

#endif
