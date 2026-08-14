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
    direction(1),
    capacity(0),
    mGame(game)
{
    position.x = 6;
    position.y = 12;
}

Frogger::~Frogger() {
//    free(segments);
}


void Frogger::Reset(SDL_Point point) {
    size = 0;
    direction = rand()%4;
}

SDL_Point Frogger::Position() {
    return position;
}


int Frogger::GetDirection() {
    return direction;
}

size_t Frogger::Size() {
    return size;
}

void Frogger::Move(int mDirection) {
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
}

bool Frogger::ContainsPoint(SDL_Point point ) {
    bool rValue = false;
    return rValue;
}

