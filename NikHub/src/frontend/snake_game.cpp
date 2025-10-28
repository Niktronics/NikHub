#include "frontend/snake_game.h"

using namespace std;

vector<pair<int,int>> snake = { {50,50}, {40,50}, {30,50} };
int directionX = 1; // 1 = right, -1 = left, 0 = no mov
int directionY = 0; // -1 = down, 1 = up, 0 = no  mov
vector<pair<int,int>> food = { {random(31), random(23)}, {random(31), random(23)}, {random(31), random(23)} };


void SnakeGame::init() {    
    tft.fillScreen(TFT_BLACK);
    initialized = true;
}

void SnakeGame::drawMenu() {
    if (!initialized) init();

    while (food.size() < 3) {
        int fx = random(0, 31);
        int fy = random(0, 23);
        food.push_back({fx, fy});
    }

    int newHeadX = snake[0].first + directionX * 10;
    int newHeadY = snake[0].second + directionY * 10;

    if (newHeadX < 0) newHeadX = 310;
    if (newHeadX > 310) newHeadX = 0;
    if (newHeadY < 0) newHeadY = 230;
    if (newHeadY > 230) newHeadY = 0;

    snake[0] = {newHeadX, newHeadY};

    // for (int i = snake.size() - 1; i > 0; i--) {
    //     tft.fillRect(snake[], pos.second, 10, 10, TFT_GREEN);
    //     if (pos != snake[0]) continue;
        
    // }

    for (auto pos : food) {
        tft.fillRect(pos.first * 10, pos.second * 10, 10, 10, TFT_RED);
    }

}

String SnakeGame::handleTouch(int x, int y, bool swipeLeft, bool swipeRight, bool swipeUp, bool swipeDown, bool mediumPress) {
    if(swipeLeft) {
        directionX = -1;
        directionY = 0;
    } else if(swipeRight) {
        directionX = 1;
        directionY = 0;
    } else if(swipeUp) {
        directionX = 0;
        directionY = -1;
    } else if(swipeDown) {
        directionX = 0;
        directionY = 1;
    }
    return "";
}