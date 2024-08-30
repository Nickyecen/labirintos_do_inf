#include "include/game.hpp"

#include "include/player.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <sstream>

char Game::run() {

    char state = 'm';
    bool shouldQuit = false;

    DisableCursor();

    Player player({8, 8});

    float rot = 0.0f;

    Map map("../maps/1.map");

    while(!shouldQuit && !WindowShouldClose()) {

        std::stringstream ss;
        ss<<"FPS: "<<(int) (1.0f/GetFrameTime());

        player.update(map);

        BeginDrawing();
        ClearBackground(BLACK);
            BeginMode3D(*player.getCamera());
                map.draw(true); 
            EndMode3D();
            DrawText(ss.str().c_str(), 0, 0, 24, WHITE);
        EndDrawing();

    }

    return state;
}
