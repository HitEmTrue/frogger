#include <SDL3/SDL_rect.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <format>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

using namespace std;

#include "Frogger.h"
#include "Game.h"

Frogger::Frogger(Game& game) 
    : size(0),
    direction(UP),
    capacity(0),
    isMoving(false),
    movingFrame(0),
    movingSteps(4),
    mGame(game)
{
    position.x = 6;
    position.y = 12;
    prevPosition.x = 0;
    prevPosition.y = 0;
}

Frogger::~Frogger() {
//    free(segments);
}


void Frogger::Reset(SDL_Point point) {
    size = 0;
    direction = UP;
}

SDL_Point Frogger::Position() {
    return position;
}

SDL_Point Frogger::PrevPosition() {
    return prevPosition;
}

bool Frogger::IsMoving() {
    return isMoving;
}

void Frogger::SetIsMoving(bool mIsMoving) {
    isMoving = mIsMoving;
}

int Frogger::MovingFrame() {
    return movingFrame;
}

int Frogger::MovingSteps() {
    return movingSteps;
}

int Frogger::Direction() {
    return direction;
}

size_t Frogger::Size() {
    return size;
}

void Frogger::Move(int mDirection) {

    prevPosition.x = position.x;
    prevPosition.y = position.y;
    isMoving = true;

    switch (mDirection) {
        case (UP):
            if (position.y > 0) {
                position.y--;
            }
            break;
        case (DOWN):
            if (position.y < 12) {
                position.y++;
            }
            break;
        case (RIGHT):
            if (position.x < 13) {
                position.x++;
            }
            break;
        case (LEFT):
            if (position.x > 0) {
                position.x--;
            }
            break;
        default:
            break;
    }

    direction = mDirection;

    // std::string debug = std::format("Frog.Move() x: {} y: {} \n",
    //         Position().x, Position().y);
    // printf("%s",debug.c_str());
    // debug = std::format("Move() PrevX: {} PrevY: {}\n",
    //         PrevPosition().x, PrevPosition().y);
    // printf("%s",debug.c_str());
}

bool Frogger::ContainsPoint(SDL_Point point ) {
    bool rValue = false;
    return rValue;
}

