#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "test.h"

std::vector<Color> rndColor {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
class Card;
Card* heldCard = nullptr;
Vector2 mousePos{};

enum class Rarity {
  COMMON,
  UNCOMMON,
  RARE,
  EPIC,
  LEGENDARY,
};


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
      if(heldCard == nullptr && IsMouseButtonDown(0) && (CheckCollisionPointRec(mousePos, bounds))){
        held = true;
        heldCard = this;
      } else if (!IsMouseButtonDown(0)) {
        held = false;
        heldCard = nullptr;
      }

      return held;
    }
    

    void moveCard(){
      if(isHeld()){
        position.x = mousePos.x -= w/2;
        position.y = mousePos.y -= h/2;

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

  int cardCount{15};

  // spawn {cardCount} amount of cards
  for(int i{0}; i != cardCount; ++i){
    activeCards.emplace_back(rand() % screenWidth-10, rand() % screenHeight-10, 200, 300);
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
      activeCards[i].isHeld();
    }

    if(heldCard != nullptr){
      heldCard->moveCard();
      std::cout << heldCard << "\n";
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
