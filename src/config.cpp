#include "include/config.hpp"
#include <raylib.h>

Config::Config(const std::string path) 
: path(path) {
    this->fps = GetMonitorRefreshRate(GetCurrentMonitor());
    this->load();
}

void Config::save() {
    std::ofstream outFile(path, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&windowWidth), sizeof(windowWidth));
        outFile.write(reinterpret_cast<const char*>(&windowHeight), sizeof(windowHeight));
        outFile.close();
    }
}

void Config::load() {
    std::ifstream inFile(path, std::ios::binary);
    if (inFile.is_open()) {
        inFile.read(reinterpret_cast<char*>(&windowWidth), sizeof(windowWidth));
        inFile.read(reinterpret_cast<char*>(&windowHeight), sizeof(windowHeight));
        inFile.close();
    } else {
        this->save();
    }
}

int Config::getWindowWidth()   { return windowWidth; }
int Config::getWindowHeight()  { return windowHeight; }
