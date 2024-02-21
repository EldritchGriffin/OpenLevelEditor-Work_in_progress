#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

class circle
{
public:
    Vector2 position;
    float radius;
    Color color;
    circle(Vector2 position, float radius, Color color) : position(position), radius(radius), color(color) {}
    void draw()
    {
        DrawCircleV(position, radius, color);
    }
};

void DrawGrid(Camera2D camera)
{
    // Draw a grid
    for (int i = -20; i <= 20; i++)
    {
        if (i == 0)
        {
            DrawLine(i * 40, -20 * 40, i * 40, 20 * 40, RED);
            DrawLine(-20 * 40, i * 40, 20 * 40, i * 40, RED);
        }
        else
        {
            DrawLine(i * 40, -20 * 40, i * 40, 20 * 40, Fade(GRAY, 0.6f));
            DrawLine(-20 * 40, i * 40, 20 * 40, i * 40, Fade(GRAY, 0.6f));
        }
    }
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 640;
    const int screenHeight = 400;
    Vector2 mousePos = {0.0f, 0.0f};

    InitWindow(screenWidth, screenHeight, "SimpleLevelEditor");

    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){0.0f, 0.0f};
    // camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    std::vector<circle> circles;
    while (!WindowShouldClose())
    {
        mousePos = GetMousePosition();
        Vector2 worldMousePos = GetScreenToWorld2D(mousePos, camera);
        const int gridSize = 40;
        Vector2 snappedPosition;
        int biasx = worldMousePos.x >= 0 ? gridSize / 2 : -gridSize / 2;
        int biasy = worldMousePos.y >= 0 ? gridSize / 2 : -gridSize / 2;
        snappedPosition.x = (int)((worldMousePos.x + biasx) / gridSize) * gridSize;
        snappedPosition.y = (int)((worldMousePos.y + biasy) / gridSize) * gridSize;
        // move the camera
        if (IsKeyDown(KEY_W))
        {
            camera.offset.y += 10;
        }
        if (IsKeyDown(KEY_S))
        {
            camera.offset.y -= 10;
        }
        if (IsKeyDown(KEY_A))
        {
            camera.offset.x += 10;
        }
        if (IsKeyDown(KEY_D))
        {
            camera.offset.x -= 10;
        }
        // draw a circle that snaps to the grid based on the mouse position in the world even if the grid isnt aligned with the screen without using predifined functions
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // convert snapped position to world position
            Vector2 worldSnappedPosition = GetWorldToScreen2D(snappedPosition, camera);
            circles.push_back(circle(worldSnappedPosition, 5, BLUE));
        }
        BeginDrawing();
        ClearBackground(DARKGRAY);
        BeginMode2D(camera);
        DrawGrid(camera);
        for (auto c : circles)
        {
            c.draw();
            // draw a line connecting the circles
            if (circles.size() > 1)
            {
                for (int i = 0; i < circles.size() - 1; i++)
                {
                    DrawLineV(circles[i].position, circles[i + 1].position, WHITE);
                }
            }
        }
        EndMode2D();
        EndDrawing();
    }

    // De-Initialization

    CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}
