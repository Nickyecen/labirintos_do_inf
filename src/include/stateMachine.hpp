#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <raylib.h>

#include "config.hpp"
#include "menu.hpp"
#include "game.hpp"

#define STATE_MENU 'm'
#define STATE_GAME 'g'
#define STATE_QUIT 'q'

class StateMachine {
    public:
        static void run();
};

#endif
