#include <raylib.h>
#include <raymath.h>

#define WORKSPACE_WIDTH 600
#define WORKSPACE_HEIGHT WORKSPACE_WIDTH
#define UIPANEL_WIDTH 200
#define UIPANEL_HEIGHT WORKSPACE_HEIGHT

int main() {
    const int screenWidth = WORKSPACE_WIDTH + UIPANEL_WIDTH;
    const int screenHeight = WORKSPACE_HEIGHT > UIPANEL_HEIGHT ? WORKSPACE_HEIGHT : UIPANEL_HEIGHT;
	const float zlvl[] = {
		.25f, .5f, .75f, // Zoom-in, make everything bigger
		1.f,             // Neutral, no zoom
		2.f, 3.f, 4.f    // Zoom-out, make everything smaller
	};

	unsigned int zlvl_idx = 3;

    InitWindow( screenWidth, screenHeight, "rltiler - Tilemap Slicer" );
	SetTargetFPS( 60 );
 
	Texture2D tilemap = { 0 };
	Camera2D camera = {
		.target = (Vector2) { .x = tilemap.width / 2.f, .y = tilemap.height / 2.f },
		.offset = (Vector2) { .x = WORKSPACE_WIDTH / 2.f, .y = WORKSPACE_HEIGHT / 2.f },
		.rotation = .0f,
		.zoom = 1.f
	};
	bool dragging = false;
	Vector2 prevmouse = { 0 };

	while ( !WindowShouldClose() ) {
		if ( IsKeyDown( KEY_UP ) || IsKeyDown( KEY_W ) )
			camera.target.y -= 5.f;
		if ( IsKeyDown( KEY_DOWN ) || IsKeyDown( KEY_S ) )
			camera.target.y += 5.f;
		if ( IsKeyDown( KEY_LEFT ) || IsKeyDown( KEY_A ) )
			camera.target.x -= 5.f;
		if ( IsKeyDown( KEY_RIGHT ) || IsKeyDown( KEY_D ) )
			camera.target.x += 5.f;

		int scroll = (int)GetMouseWheelMove();
		if ( scroll > 0 && zlvl_idx < 6 )
			++zlvl_idx;
		if ( scroll < 0 && zlvl_idx > 0 )
			--zlvl_idx;

		camera.zoom = zlvl[zlvl_idx];

		Vector2 mouse = GetMousePosition();

		if ( IsMouseButtonPressed( MOUSE_RIGHT_BUTTON ) ) {
			dragging = true;
			prevmouse = mouse;
		}

		if ( IsMouseButtonReleased( MOUSE_RIGHT_BUTTON ) )
			dragging = false;

		if ( dragging ) {
			Vector2 delta = Vector2Scale( Vector2Subtract( prevmouse, mouse ), 1.f / camera.zoom );
			camera.target = Vector2Add( camera.target, delta );
			prevmouse = mouse;
		}

		if ( IsFileDropped() ) {
			FilePathList files = LoadDroppedFiles();
			char * file = 0;
			for ( int i = 0; i < files.count; ++i ) {
				file = files.paths[i];
			}
			if ( file ) {
				UnloadTexture( tilemap );
				tilemap = LoadTexture( file );
			}
			UnloadDirectoryFiles( files );
		}

		BeginDrawing();
		ClearBackground( RAYWHITE );

		BeginScissorMode( 0, 0, WORKSPACE_WIDTH, WORKSPACE_HEIGHT );
		BeginMode2D( camera );

        DrawTexture( tilemap, 0, 0, WHITE );

		EndMode2D();
		EndScissorMode();

		DrawRectangleLines( WORKSPACE_WIDTH, 0, UIPANEL_WIDTH, UIPANEL_HEIGHT, BLACK );
		DrawText( TextFormat( "FPS: %d", GetFPS() ), WORKSPACE_WIDTH + 10, 10, 14, BLACK );
		DrawText( TextFormat( "Zoom-Level: %d", zlvl_idx ), WORKSPACE_WIDTH + 10, 30, 14, BLACK );
		DrawText( TextFormat( "Zoom: %.02f", zlvl[zlvl_idx] ), WORKSPACE_WIDTH + 10, 50, 14, BLACK );

		EndDrawing();
    }

	UnloadTexture( tilemap );
    CloseWindow();
    return 0;
}
