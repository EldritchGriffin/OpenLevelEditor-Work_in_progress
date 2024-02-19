#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

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
    const int screenWidth = 800;
    const int screenHeight = 450;
    Vector2 mousePos = {0.0f, 0.0f};

    InitWindow(screenWidth, screenHeight, "SimpleLevelEditor");

    Camera2D camera = {0};
    camera.zoom = 1.0f;
    camera.target = (Vector2){0.0f, 0.0f};

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        mousePos = GetMousePosition();
        Vector2 worldMousePos = GetScreenToWorld2D(mousePos, camera);
        const int gridSize = 40;
        Vector2 snappedPosition;
        snappedPosition.x = (int)(worldMousePos.x / gridSize) * gridSize;
        snappedPosition.y = (int)(worldMousePos.y / gridSize) * gridSize;
        // move the camera
        if (IsKeyDown(KEY_W))
        {
            camera.target.y -= 10;
        }
        if (IsKeyDown(KEY_S))
        {
            camera.target.y += 10;
        }
        if (IsKeyDown(KEY_A))
        {
            camera.target.x -= 10;
        }
        if (IsKeyDown(KEY_D))
        {
            camera.target.x += 10;
        }
        // draw a circle that snaps to the grid based on the mouse position in the world even if the grid isnt aligned with the screen without using predifined functions
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            // convert snapped position to world position
            Vector2 worldSnappedPosition = GetWorldToScreen2D(snappedPosition, camera);
            DrawCircleV(worldSnappedPosition, 5, BLUE);
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);
        BeginMode2D(camera);
        DrawGrid(camera);
        EndMode2D();
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
