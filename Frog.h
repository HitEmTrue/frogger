#pragma once

#include <SDL3/SDL_rect.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <filesystem>
#include <format>

class Game;

using namespace std;


class Frog {
    size_t size;
    int direction;
    size_t capacity;
    SDL_Point position;
    bool isMoving;
    int movingSteps;
    SDL_Point prevPosition;
    Game& mGame;

    public:
        Frog(Game& game); 

        ~Frog();

        int movingFrame;

        void Reset(); 
        
        SDL_Point Position();

        SDL_Point PrevPosition();

        bool IsMoving();

        void SetIsMoving(bool mIsMoving);

        int MovingFrame();

        int MovingSteps();

        int Direction();

        size_t Size();

        void Move(int mDirection);

//        bool ContainsPoint(SDL_Point point );


}; 
