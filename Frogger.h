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
    SDL_Point position;
    Game& mGame;

    public:
        Frogger(Game& game); 

        ~Frogger();

        void Reset(SDL_Point point); 
        

        SDL_Point Position();

        int GetDirection();

        size_t Size();

        void Move(int mDirection);

        bool ContainsPoint(SDL_Point point );


}; 
