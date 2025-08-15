#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "test.h"

class Card;
float delta{};
Vector2 mousePos{};
Card* heldCard = nullptr;
Color rndColor[6]{RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};


/////////////
// CLASSES //
/////////////

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
    bool held = false;
    Rarity rarity{};
    Rectangle bounds{x, y, w, h};
    Color col{};


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

        bounds.x = Lerp(bounds.x, position.x, 20 * delta);
        bounds.y = Lerp(bounds.y, position.y, 20 * delta);
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


// MAIN
int main()
{
  // Window settings / config variables 
  const int screenWidth{1024};
  const int screenHeight{768};
  const int mon{GetCurrentMonitor()};
  float refreshRate = GetMonitorRefreshRate(0);
  bool _fps{false};

  InitWindow(screenWidth, screenHeight, "Misc Card Game");
  //pseudo v-sync
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

  // just here to make sure my header works. Will probably move class decs to header.
  testFunction();

  // Game Variables
  std::vector<Card> activeCards;
  int cardCount{2};




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

    if(IsKeyPressed(KEY_SPACE)){
      ++cardCount;
    } else if (IsKeyPressed(KEY_X)){
      --cardCount;
    }

    // spawn {cardCount} amount of cards
    for(int i{0}; i != cardCount; ++i){
      activeCards.emplace_back(rand() % screenWidth-10, rand() % screenHeight-10, 200, 300);
    }

    for (int i{0}; i != cardCount; ++i){
      activeCards[i].isHeld();
    }

    if(heldCard != nullptr){
      heldCard->moveCard();
    }

    // DRAWING //
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i{cardCount-1}; i != -1; --i){
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
