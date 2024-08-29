#include "include/menu.hpp"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

char Menu::run() {
   
    char nextState = 'q';
    bool shouldQuit = false;

    SetExitKey(0);
    EnableCursor();

    while(!shouldQuit && !WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(DARKGRAY);

            std::string title = "Labirintos do INF";
            std::string subtitle = "Remake";

            int titleSize = GetScreenHeight()/12;
            int subtitleSize = GetScreenHeight()/16;

            int titleLength = MeasureText(title.c_str(), titleSize);
            int subtitleLength = MeasureText(subtitle.c_str(), subtitleSize);

            DrawText(title.c_str(), (GetScreenWidth() - titleLength)/2, 10, titleSize, RAYWHITE);
            DrawText(subtitle.c_str(), (GetScreenWidth() - subtitleLength)/2, titleSize + 10, subtitleSize, RAYWHITE);

            float buttonWidth = 240.0f;
            float buttonHeight = 60.0f;
            float spacing = 10.0f;
            if(GuiButton((Rectangle){(GetScreenWidth()-buttonWidth)/2.0f, GetScreenHeight()/2.0f, buttonWidth, buttonHeight}, "Novo Jogo")) {
                nextState = 'g';
                shouldQuit = true;
            }
            if(GuiButton((Rectangle){(GetScreenWidth()-buttonWidth)/2.0f, GetScreenHeight()/2.0f + buttonHeight + spacing, buttonWidth, buttonHeight}, "Carregar Jogo")) {
            }
            if(GuiButton((Rectangle){(GetScreenWidth()-buttonWidth)/2.0f, GetScreenHeight()/2.0f + 2*buttonHeight + 2*spacing, buttonWidth, buttonHeight}, "Opções")) {
            }
            if(GuiButton((Rectangle){(GetScreenWidth()-buttonWidth)/2.0f, GetScreenHeight()/2.0f + 3*buttonHeight + 3*spacing, buttonWidth, buttonHeight}, "Sair")) {
                shouldQuit = true;
            }

        EndDrawing();
    }

    return nextState;

}
