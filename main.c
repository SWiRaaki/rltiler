#include <raylib.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "rltiler - Tilemap Slicer");
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, rltiler!", 300, 250, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
