#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <condition_variable>
#include <string>
#include <iostream>
#include <fstream>
#include <raylib.h>

class Config {
    // VARIABLES
    private:
        const std::string path;

        int windowWidth = 800;
        int windowHeight = 600;
        int fps;

    // METHODS
    public:
        Config(const std::string path);

        void save();
        void load();

        int getWindowWidth();
        int getWindowHeight();
};

#endif
