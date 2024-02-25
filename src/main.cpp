#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include <rlgl.h>
#include <sceneManager.hpp>
#include <scene.hpp>

static void NewProjectButton();
static void LoadProjectButton();
static void SaveProjectButton();
static void RemoveSceneButton(int index, SceneManager & sceneManager, int *activeScene);
static void CreateSceneButton(char *sceneName, SceneManager &sceneManager);
static void RenameSceneButton(char *sceneName, SceneManager &sceneManager);
static void HandleSceneSelect(int *activeScene, SceneManager &sceneManager);

std::string styleString(std::string str)
{
    if(str.size() >= 25)
    {
        str = str.substr(0, 22);
        str += "...";
        return (str);
    }
    return str;
}

char* getSceneNames(SceneManager &sceneManager) {
    std::vector<Scene*> scenes = sceneManager.getScenes();
    if (scenes.empty()) {
        return NULL; 
    }

    std::string sceneNames;
    for (auto scene : scenes) {
        if (!sceneNames.empty()) {
            sceneNames += ";";
        }
        sceneNames += styleString(scene->getName());
    }

    char* res = new char[sceneNames.size() + 1];
    std::copy(sceneNames.begin(), sceneNames.end(), res);
    res[sceneNames.size()] = '\0';

    return res;
}


void drawGui(SceneManager &sceneManager)
{

    static int     sceneListScrollIndex = 0;
    static int     oldSceneListActive = 0;
    static int     sceneListActive = 0;
    static bool    createSceneTextBoxEditMode = false;
    static char    sceneName[128] = "SceneName";
    char           *sceneList = getSceneNames(sceneManager);

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
    GuiGroupBox((Rectangle){ 24, 24, 288, 56 }, "Project Manager");
    if (GuiButton((Rectangle){ 40, 40, 72, 24 }, "#008#New")) NewProjectButton(); //TODO: create logic for creating a new project.
    if (GuiButton((Rectangle){ 128, 40, 72, 24 }, "#004#Load")) LoadProjectButton(); //TODO: create logic for loading project.
    if (GuiButton((Rectangle){ 216, 40, 72, 24 }, "#002#Save")) SaveProjectButton(); //TODO: create logic for saving project
    GuiGroupBox((Rectangle){ 24, 96, 288, 576 }, "Scene Manager");
    GuiListView((Rectangle){ 72, 240, 192, 344 }, sceneList, &sceneListScrollIndex, &sceneListActive);
    if(!sceneManager.getScenes().empty())
        HandleSceneSelect(&sceneListActive, sceneManager);
    GuiLabel((Rectangle){ 72, 216, 120, 24 }, "Scenes:");
    if (GuiButton((Rectangle){ 144, 592, 120, 32 }, "#113#Remove Scene")) RemoveSceneButton(sceneListActive, sceneManager, &sceneListActive); 
    if (GuiTextBox((Rectangle){ 72, 144, 192, 24 }, sceneName, 128, createSceneTextBoxEditMode)) createSceneTextBoxEditMode = !createSceneTextBoxEditMode;
    if (GuiButton((Rectangle){ 192, 176, 72, 24 }, "#112#Create")) CreateSceneButton(sceneName, sceneManager); 
    if (GuiButton((Rectangle){ 112, 176, 72, 24 }, "#022#Rename")) RenameSceneButton(sceneName, sceneManager);
    delete [] sceneList;
}

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    SceneManager sceneManager;
    InitWindow(screenWidth, screenHeight, "SimpleLevelEditor");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    GuiLoadStyle("styles/dark/style_dark.rgs");
    SetTargetFPS(60);
    try
    {
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

static void NewProjectButton()
{
    // TODO: Implement control logic
}
static void LoadProjectButton()
{
    // TODO: Implement control logic
}
static void SaveProjectButton()
{
    // TODO: Implement control logic
}
static void RemoveSceneButton(int index, SceneManager &sceneManager, int *activeScene)
{
    try
    {
        sceneManager.RemoveScene(sceneManager.getScenes().at(index)->getName());
        if(*activeScene != 0)
            *activeScene -= 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
static void CreateSceneButton(char *sceneName, SceneManager & sceneManager)
{
    try
    {
        sceneManager.createScene(sceneName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
static void RenameSceneButton(char *sceneName, SceneManager & sceneManager)
{
    try
    {
        sceneManager.renameActiveScene(sceneName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

static void HandleSceneSelect(int *activeScene, SceneManager &sceneManager)
{
    static int oldActiveScene = 0;
    if(*activeScene == -1)
        *activeScene = oldActiveScene;
    else if(sceneManager.getScenes().at(*activeScene)->getName() != sceneManager.getActiveScene())
        sceneManager.SetActiveScene(sceneManager.getScenes().at(*activeScene)->getName());
    oldActiveScene = *activeScene;
    return;
}
