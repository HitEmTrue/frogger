#pragma once

#include <SDL3/SDL_rect.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <filesystem>
#include <format>

class Game;

using namespace std;


class Frogger {
    size_t size;
    int direction;
    size_t capacity;
    Game& mGame;

    public:
        Frogger(Game& game); 

        ~Frogger();

        void Reset(SDL_Point point); 

        int GetDirection();

        size_t Size();

        void SetDirection(int newDirection);

        bool ContainsPoint(SDL_Point point );
}; 
