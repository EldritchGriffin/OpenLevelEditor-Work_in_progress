#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include <rlgl.h>
#include <sceneManager.hpp>
#include <scene.hpp>

void drawGui(SceneManager &sceneManager)
{
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    SceneManager sceneManager;
    InitWindow(screenWidth, screenHeight, "SimpleLevelEditor");
    SetTargetFPS(60);
    try
    {
        sceneManager.createScene("scene1");
        sceneManager.createScene("scene2");
        sceneManager.createScene("scene3");
        sceneManager.SetActiveScene("scene1");
        while (!WindowShouldClose())
        {
            sceneManager.Update();
            BeginDrawing();
            drawGui(sceneManager);
            ClearBackground(RAYWHITE);
            sceneManager.Draw();
            EndDrawing();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    CloseWindow();
    return 0;
}
