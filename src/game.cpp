#include "include/game.hpp"

#include "include/player.hpp"

#include <raylib.h>

char Game::run() {

    char state = 'm';
    bool shouldQuit = false;

    DisableCursor();

    Player player;

    float rot = 0.0f;

    Map map("../maps/1.map");

    while(!shouldQuit && !WindowShouldClose()) {
        rot += 0.1f;

        player.update();

        BeginDrawing();
        ClearBackground(BLACK);
            BeginMode3D(*player.getCamera());
                map.draw(); 
            EndMode3D();
        EndDrawing();

    }

    return state;
}
