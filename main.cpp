#include <raylib.h>
#include <iostream>

int main()
{

  const int screenWidth{1280};
  const int screenHeight{720};
  const int refreshRate{GetMonitorRefreshRate(GetCurrentMonitor())};
  float delta{};
  bool _fps{true};

  InitWindow(screenWidth, screenHeight, "The Game");
  SetTargetFPS(refreshRate);

  // Game Variables
  const float gravity{750};
  const float maxSpeed{500};
  const float acceleration{5};
  const float friction{5};

  Rectangle player{(float)screenWidth/2 - 50, (float)screenHeight/2 - 50, 100, 100};
  Rectangle floor{(float)screenWidth/2 - 500, (float)screenHeight/2 + 250 - 25, 1000, 50};

  std::cout << "Shut up clangd\n";

  while (!WindowShouldClose())
  {
    delta = GetFrameTime();
    // UPDATE //

    // Toggle framerate
     if(IsKeyPressed(KEY_F1) && !_fps) {
      _fps = true;
    } else if (IsKeyPressed(KEY_F1) && _fps) {
      _fps = false;
    }

    int direction = 0;
    if(IsKeyDown(KEY_D)) direction += 1;
    if(IsKeyDown(KEY_A)) direction -= 1;
    player.x += direction * maxSpeed * delta;

    if(!CheckCollisionRecs(player, floor)) {
      player.y += gravity * delta;
    } 


    // DRAWING //
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangle(player.x, player.y, player.width, player.height, SKYBLUE);
    DrawRectangle(floor.x, floor.y, floor.width, floor.height, RED);

    if(_fps) {
      DrawFPS(10, 10);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
