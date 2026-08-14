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
}

Frogger::~Frogger() {
//    free(segments);
}


void Frogger::Reset(SDL_Point point) {
    size = 0;
    direction = rand()%4;
}

int Frogger::GetDirection() {
    return direction;
}

size_t Frogger::Size() {
    return size;
}

void Frogger::SetDirection(int newDirection) {
    direction = newDirection;
}



bool Frogger::ContainsPoint(SDL_Point point ) {
    bool rValue = false;
    return rValue;
}

