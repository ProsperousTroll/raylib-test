#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "test.h"

std::vector<Color> rndColor {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
Vector2 mousePos{};

enum class Rarity {
  COMMON,
  UNCOMMON,
  RARE,
  EPIC,
  LEGENDARY,
};

class Card;

Card* currentlyHeldCard = nullptr;

class Card {
  public: 
    float x{};
    float y{};
    Vector2 position{x, y};
    float w{};
    float h{};
    Rarity rarity{};
    Rectangle bounds{x, y, w, h};
    Color col{};

    bool held = false;

    // methods
    void drawColor(){
      DrawRectangleRec(bounds, col);
    }

    bool isHeld(){
      if(IsMouseButtonDown(1) && (CheckCollisionPointRec(mousePos, bounds))){
        held = true;
      } else if (!IsMouseButtonDown(1)) {
        held = false;
      }
      return held;

      if(currentlyHeldCard == nullptr){
        if (IsMouseButtonDown(0) && CheckCollisionPointRec(mousePos, bounds)) {
          currentlyHeldCard = this;
          held = true;
        }
      }

      if(currentlyHeldCard == this && IsMouseButtonDown(0)){
        held = true;
      }

      if (!IsMouseButtonDown(0) && currentlyHeldCard == this){
        held = false;
        currentlyHeldCard = nullptr;
      }

    }
    

    void moveCard(){
      isHeld();
      if(held){
        position.x = mousePos.x -= w/50;
        position.y = mousePos.y -= h/50;

        bounds.x = Lerp(bounds.x, position.x, 0.002);
        bounds.y = Lerp(bounds.y, position.y, 0.002);
      }          
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
      col = rndColor[rand() % 6];
    }
  private:
};


int main()
{
  // Window settings / config variables 
  const int screenWidth{1024};
  const int screenHeight{768};
  int refreshRate{GetMonitorRefreshRate(GetCurrentMonitor())};
  float delta{};
  bool _fps{false};

  InitWindow(screenWidth, screenHeight, "The Game");
  SetTargetFPS(refreshRate);

  // just here to make sure my header works
  testFunction();

  // Game Variables






  std::vector<Card> activeCards;

  int cardCount{50};
  //activeCards.emplace_back();
  for(int i{0}; i != cardCount; ++i){
    activeCards.emplace_back(rand() % screenWidth-10, rand() % screenHeight-10, 100, 150);
  }


  while (!WindowShouldClose())
  {
    // UPDATE //
    delta = GetFrameTime();
    mousePos = GetMousePosition();

    // Toggle framerate
     if(IsKeyPressed(KEY_FIVE) && !_fps) {
      _fps = true;
    } else if (IsKeyPressed(KEY_FIVE) && _fps) {
      _fps = false;
    }

    for (int i{0}; i != cardCount; ++i){
      activeCards[i].moveCard();
    }

    // DRAWING //
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i{0}; i != cardCount; ++i){
      activeCards[i].drawColor();
    }

    if(_fps) {
      DrawFPS(10, 10);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
