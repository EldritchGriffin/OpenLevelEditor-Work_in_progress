#define RAYGUI_IMPLEMENTATION
#define RAYGIZMO_IMPLEMENTATION
#define PLATFORM_DESKTOP
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include <rlgl.h>
#include <sceneManager.hpp>
#include <scene.hpp>
#include <raygizmo.h>

static void NewProjectButton();
static void LoadProjectButton();
static void SaveProjectButton();
static void RemoveSceneButton(int index, SceneManager &sceneManager, int *activeScene);
static void CreateSceneButton(char *sceneName, SceneManager &sceneManager);
static void RenameSceneButton(char *sceneName, SceneManager &sceneManager);
static void HandleSceneSelect(int *activeScene, SceneManager &sceneManager);

void ZoomCamera(Camera &camera)
{
    static float cameraDistance = 10.0f;
    static float minCameraDistance = 1.0f;
    static float maxCameraDistance = 50.0f;
    static float scrollSpeed = 0.5f;
    cameraDistance -= (GetMouseWheelMove() * scrollSpeed);
    if (cameraDistance < minCameraDistance)
    {
        cameraDistance = minCameraDistance;
    }
    else if (cameraDistance > maxCameraDistance)
    {
        cameraDistance = maxCameraDistance;
    }
    Vector3 forward = Vector3Subtract(camera.target, camera.position);
    forward = Vector3Normalize(forward);
    camera.position = Vector3Subtract(camera.target, Vector3Scale(forward, cameraDistance));
}
void OrbitAndPanCamera(Camera &camera)
{
    static Vector2 previousMousePosition = {0};
    static bool isMiddleMouseButtonPressed = false;
    static bool isShiftKeyPressed = false;

    if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
    {
        previousMousePosition = GetMousePosition();
        isMiddleMouseButtonPressed = true;
    }
    else if (IsMouseButtonReleased(MOUSE_MIDDLE_BUTTON))
    {
        isMiddleMouseButtonPressed = false;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        isShiftKeyPressed = true;
    }
    else if (IsKeyUp(KEY_LEFT_SHIFT))
    {
        isShiftKeyPressed = false;
    }

    if (isMiddleMouseButtonPressed)
    {
        Vector2 currentMousePosition = GetMousePosition();
        float deltaX = (currentMousePosition.x - previousMousePosition.x) / 2;
        float deltaY = (currentMousePosition.y - previousMousePosition.y) / 2;

        if (isShiftKeyPressed)
        {
            float speed = 0.03f;

            Vector3 forward = Vector3Subtract(camera.target, camera.position);
            Vector3 right = Vector3CrossProduct(camera.up, forward);
            right = Vector3Normalize(right);
            Vector3 up = Vector3CrossProduct(forward, right);
            up = Vector3Normalize(up);
            Vector3 pan = Vector3Add(Vector3Scale(right, deltaX * speed), Vector3Scale(up, deltaY * speed));
            camera.position = Vector3Add(camera.position, pan);
            camera.target = Vector3Add(camera.target, pan);
        }
        else
        {
            float speed = 0.01f;
            float radius = Vector3Distance(camera.position, camera.target);
            float phi = atan2(camera.position.z - camera.target.z, camera.position.x - camera.target.x);
            float theta = atan2(sqrt(pow(camera.position.x - camera.target.x, 2) + pow(camera.position.z - camera.target.z, 2)), camera.position.y - camera.target.y);
            phi += deltaX * speed;
            theta += deltaY * speed;
            if (theta < 0.1f)
                theta = 0.1f;
            if (theta > PI - 0.1f)
                theta = PI - 0.1f;
            camera.position.x = radius * sinf(theta) * cosf(phi) + camera.target.x;
            camera.position.y = radius * cosf(theta) + camera.target.y;
            camera.position.z = radius * sinf(theta) * sinf(phi) + camera.target.z;
        }

        previousMousePosition = currentMousePosition;
    }
}
// function that trims a string and truncates (...) if the string is too long @param str string to be styled
std::string styleString(std::string str)
{
    if (str.size() >= 25)
    {
        str = str.substr(0, 22);
        str += "...";
        return (str);
    }
    return str;
}

char *getSceneNames(SceneManager &sceneManager)
{
    std::vector<Scene *> scenes = sceneManager.getScenes();
    if (scenes.empty())
    {
        return NULL;
    }

    std::string sceneNames;
    for (auto scene : scenes)
    {
        if (!sceneNames.empty())
        {
            sceneNames += ";";
        }
        sceneNames += styleString(scene->getName());
    }

    char *res = new char[sceneNames.size() + 1];
    std::copy(sceneNames.begin(), sceneNames.end(), res);
    res[sceneNames.size()] = '\0';

    return res;
}

void drawGui(SceneManager &sceneManager)
{

    static int sceneListScrollIndex = 0;
    static int oldSceneListActive = 0;
    static int sceneListActive = 0;
    static bool createSceneTextBoxEditMode = false;
    static char sceneName[128] = "SceneName";
    char *sceneList = getSceneNames(sceneManager);
    DrawRectangle(24, 24, 288, 648, GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    GuiGroupBox((Rectangle){24, 24, 288, 56}, "Project Manager");
    if (GuiButton((Rectangle){40, 40, 72, 24}, "#008#New"))
        NewProjectButton(); // TODO: create logic for creating a new project.
    if (GuiButton((Rectangle){128, 40, 72, 24}, "#004#Load"))
        LoadProjectButton(); // TODO: create logic for loading project.
    if (GuiButton((Rectangle){216, 40, 72, 24}, "#002#Save"))
        SaveProjectButton(); // TODO: create logic for saving project
    GuiGroupBox((Rectangle){24, 96, 288, 576}, "Scene Manager");
    GuiListView((Rectangle){72, 240, 192, 344}, sceneList, &sceneListScrollIndex, &sceneListActive);
    if (!sceneManager.getScenes().empty())
        HandleSceneSelect(&sceneListActive, sceneManager);
    GuiLabel((Rectangle){72, 216, 120, 24}, "Scenes:");
    if (GuiButton((Rectangle){144, 592, 120, 32}, "#113#Remove Scene"))
        RemoveSceneButton(sceneListActive, sceneManager, &sceneListActive);
    if (GuiTextBox((Rectangle){72, 144, 192, 24}, sceneName, 128, createSceneTextBoxEditMode))
        createSceneTextBoxEditMode = !createSceneTextBoxEditMode;
    if (GuiButton((Rectangle){192, 176, 72, 24}, "#112#Create"))
        CreateSceneButton(sceneName, sceneManager);
    if (GuiButton((Rectangle){112, 176, 72, 24}, "#022#Rename"))
        RenameSceneButton(sceneName, sceneManager);
    delete[] sceneList;
}

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    SceneManager sceneManager;
    InitWindow(screenWidth, screenHeight, "OpenLevelEditor");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    GuiLoadStyle("styles/cyber/style_cyber.rgs");
    Camera camera = {0};
    camera.position = (Vector3){10.0, 10.0, 10.0}; // Camera position
    camera.up = (Vector3){0.0f, 0.99f, 0.0f};      // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);
    
    try
    {
        while (!WindowShouldClose())
        {
            if (IsFileDropped())
            {
                FilePathList files = LoadDroppedFiles();
                sceneManager.addObject(files.paths[0], {0, 0, 0}, {0, 0, 0}, {1, 1, 1});
                UnloadDroppedFiles(files);
            }
            OrbitAndPanCamera(camera);
            ZoomCamera(camera);
            sceneManager.Update(camera);
            BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            if (sceneManager.isEmpty())
            {
                DrawText("No active scene", 500, 500, 50, WHITE);
            }
            else
            {
                rlEnableDepthTest();
                BeginMode3D(camera);
                rlSetLineWidth(1.0);
                DrawGrid(100, 1);
                sceneManager.Draw(camera);
                EndMode3D();
            }
            drawGui(sceneManager);
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
        if (*activeScene != 0)
            *activeScene -= 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
static void CreateSceneButton(char *sceneName, SceneManager &sceneManager)
{
    try
    {
        sceneManager.createScene(sceneName);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
static void RenameSceneButton(char *sceneName, SceneManager &sceneManager)
{
    try
    {
        sceneManager.renameActiveScene(sceneName);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

static void HandleSceneSelect(int *activeScene, SceneManager &sceneManager)
{
    static int oldActiveScene = 0;
    if (*activeScene == -1)
        *activeScene = oldActiveScene;
    else if (sceneManager.getScenes().at(*activeScene)->getName() != sceneManager.getActiveScene())
        sceneManager.SetActiveScene(sceneManager.getScenes().at(*activeScene)->getName());
    oldActiveScene = *activeScene;
    return;
}
