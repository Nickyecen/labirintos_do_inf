#include "include/game.hpp"

#include "include/player.hpp"

#include <raylib.h>

char Game::run() {

    char state = 'm';
    bool shouldQuit = false;

    DisableCursor();

    Player player;
    Mesh cube = GenMeshCube(TILE_SIZE, TILE_SIZE, TILE_SIZE);
    Model floorModel = LoadModelFromMesh(cube);

    float rot = 0.0f;

    while(!shouldQuit && !WindowShouldClose()) {
        rot += 0.1f;

        player.update();

        BeginDrawing();
        ClearBackground(WHITE);
            BeginMode3D(*player.getCamera());
 
                DrawModelEx(floorModel, {3, 0, 0}, {0, 1, 0}, rot, {1,1,1}, RED); 

            EndMode3D();
        EndDrawing();

    }

    return state;
}
