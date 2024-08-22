#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <raylib.h>

#include "config.hpp"
#include "menu.hpp"

#define STATE_MENU 'm'
#define STATE_QUIT 'q'

class StateMachine {
    public:
        static void run();
};

#endif
