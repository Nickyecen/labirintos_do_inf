#include "include/stateMachine.hpp"

void StateMachine::run() {
    Config c("../.config");
    InitWindow(c.getWindowWidth(), c.getWindowHeight(), "Labirintos do INF");
    SetTargetFPS(60);

    char state = STATE_MENU;
    while(state != STATE_QUIT && !WindowShouldClose()) {
        switch(state) {
            case STATE_MENU:
                state = Menu::run();
                break;
            case STATE_QUIT:
                break; 
        } 
    }

    CloseWindow();
}
