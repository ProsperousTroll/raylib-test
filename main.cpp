#include <raylib.h>
#include <iostream>
#include "test.h"

int main()
{
  // Window settings / config variables 
  const int screenWidth{1024};
  const int screenHeight{768};
  int refreshRate{GetMonitorRefreshRate(GetCurrentMonitor())};
  float delta{};
  Vector2 mousePos{};
  bool _fps{false};

  InitWindow(screenWidth, screenHeight, "The Game");
  SetTargetFPS(refreshRate);

  // just here to make sure my header works
  testFunction();

  // Game Variables

  bool isHeld{false};

  enum class Rarity {
    COMMON,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY,
  };

  class Card {
    public: 

      // properties
      float x{};
      float y{};
      Vector2 position{x, y};
      int w{};
      int h{};
      Rarity rarity{};
      Rectangle bounds{};
      Image image{};

      // methods
      void drawColor(Color col){
        DrawRectangleRec(bounds, col);
      }

      void moveCard(Vector2 mouse, bool& held){
        if(IsMouseButtonDown(0) && CheckCollisionPointRec(mouse, bounds) && !held) {
          held = true;
          mouse.x -= w/2;
          mouse.y -= h/2;
          position = mouse;
          bounds.x = position.x;
          bounds.y = position.y;
        } else held = false;
      }
      
      // constructors 
      Card() {
        x = 0.0;
        y = 0.0;
        w = 100;
        h = 150;
        position = {x, y};
        bounds={x, y, w, h};
        rarity = Rarity::COMMON;
      }

      Card(float initX, float initY, int initW, int initH) {
        x = initX;
        y = initY;
        w = initW;
        h = initH;
        position = {initX, initY};
        bounds = {x, y, w, h};
      }
    private:
  };

  Card firstCard(screenWidth/2 - 100/2, screenHeight/2 - 150/2, 100, 150);


  while (!WindowShouldClose())
  {
    // UPDATE //
    delta = GetFrameTime();
    mousePos = {GetMouseX(), GetMouseY()};

    // Toggle framerate
     if(IsKeyPressed(KEY_FIVE) && !_fps) {
      _fps = true;
    } else if (IsKeyPressed(KEY_FIVE) && _fps) {
      _fps = false;
    }

     firstCard.moveCard(mousePos, isHeld);

    // DRAWING //
    BeginDrawing();

    ClearBackground(RAYWHITE);
    if(_fps) {
      DrawFPS(10, 10);
    }

    firstCard.drawColor(RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
