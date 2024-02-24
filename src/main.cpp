#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include <rlgl.h>
#include <sceneManager.hpp>
#include <scene.hpp>

std::string getSceneNames(SceneManager & sceneManager)
{
    std::vector<Scene *> scenes = sceneManager.getScenes();
    std::string sceneNames = "";
    for(auto scene : scenes)
    {
        sceneNames = sceneNames + scene->getName() + ";";
    }
    sceneNames = sceneNames.substr(0, sceneNames.size() - 1);
    return (sceneNames);
}

void drawGui(SceneManager &sceneManager)
{
    static bool Button001Pressed = false;
    static bool Button002Pressed = false;
    static bool Button003Pressed = false;
    static int ListView005ScrollIndex = 0;
    static int ListView005Active = 0;
    std::string sceneNames = getSceneNames(sceneManager);
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

    GuiGroupBox((Rectangle){ 24, 24, 288, 56 }, "Project Manager");
    Button001Pressed = GuiButton((Rectangle){ 40, 40, 72, 24 }, "#008#New"); 
    Button002Pressed = GuiButton((Rectangle){ 128, 40, 72, 24 }, "#004#Load"); 
    Button003Pressed = GuiButton((Rectangle){ 216, 40, 72, 24 }, "#002#Save"); 
    GuiGroupBox((Rectangle){ 24, 96, 288, 768 }, "Scene Manager");
    GuiListView((Rectangle){ 72, 168, 192, 176 }, sceneNames.c_str(), &ListView005ScrollIndex, &ListView005Active);
    GuiLabel((Rectangle){ 72, 144, 120, 24 }, "Scenes:");
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    SceneManager sceneManager;
    InitWindow(screenWidth, screenHeight, "SimpleLevelEditor");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    try
    {
        sceneManager.createScene("MainRoom");
        sceneManager.createScene("Stage1");
        sceneManager.createScene("Castle");
        sceneManager.SetActiveScene("MainRoom");
        GuiLoadStyle("../styles/dark/style_dark.rgs");
        while (!WindowShouldClose())
        {
            sceneManager.Update();
            BeginDrawing();
            drawGui(sceneManager);
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
