#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <filesystem>
#include <format>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#include "Game.h"
#include "Frog.h"

Game::Game()
            : mFrog(*this),
            isPaused(false),
            isGameLost(false),
            score(0),
            highScore(0),
            losses(0),
            renderer(nullptr),
            font(nullptr),
            textureGamePaused(nullptr),
            textureYouWon(nullptr),
            textureYouLost(nullptr),
            BOARD_WIDTH_TILES(WINDOW_WIDTH / TILE_SIZE),
            BOARD_HEIGHT_TILES((WINDOW_HEIGHT - SCOREBOARD_HEIGHT) / TILE_SIZE)
{
}

Game::~Game() {
}

void Game::resetGame() {
    score = 0;
    mFood.Reset();

    mFrog.Reset();
}

void Game::handleGameLost() {
    isGameLost = true;

    if (score > highScore ) {
        highScore = score;
        ComposeScoreboardText();
    }
}


void Game::ComposeScoreboardText() {

    SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Surface *text;
    std::string banner = std::format("Score : {}                  High score : {}", score, highScore);

    text = TTF_RenderText_Blended(font, banner.c_str(), 0, color); 
    if (text) {
        textureScore = SDL_CreateTextureFromSurface(renderer, text);
        SDL_DestroySurface(text);
    }
    if (!textureScore) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    }
}


void Game::ShowPaused() {
    int w = 0, h = 0;
    SDL_FRect dst;
    const float scale = 1.0f;


    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_GetTextureSize(textureGamePaused, &dst.w, &dst.h);
    dst.x = ((w / scale) - dst.w) / 2;
    dst.y = ((h / scale) - dst.h) / 2;

    /* Draw the text */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //            SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, textureGamePaused, NULL, &dst);


}

void Game::ShowYouLost() {
    int w = 0, h = 0;
    SDL_FRect dst;
    const float scale = 1.0f;


    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_GetTextureSize(textureYouLost, &dst.w, &dst.h);
    dst.x = ((w / scale) - dst.w) / 2;
    dst.y = ((h / scale) - dst.h) / 2;

    /* Draw the text */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //            SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, textureYouLost, NULL, &dst);


}

void Game::RenderScoreboard() {

    SDL_FRect border;
    border.x = 0;
    border.y = 0;
    border.h = WINDOW_HEIGHT - SCOREBOARD_HEIGHT;
    border.w = WINDOW_WIDTH;


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    //            SDL_RenderLine(renderer, 0, WINDOW_HEIGHT - SCOREBOARD_HEIGHT + 1, WINDOW_WIDTH, WINDOW_HEIGHT - SCOREBOARD_HEIGHT + 1);
    SDL_RenderRect(renderer, &border);



    int w = 0, h = 0;
    SDL_FRect dst;
    const float scale = 1.0f;

    dst.x = 5;
    dst.y = WINDOW_HEIGHT - SCOREBOARD_HEIGHT + 4;

    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_GetTextureSize(textureScore, &dst.w, &dst.h);

    /* Draw the text */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //            SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, textureScore, NULL, &dst);
}


void Game::RenderFrog() {

    //TODO check bounds on frame

    // std::string debug = std::format("Frog x: {} y: {} HEADER_HEIGHT: {}\n",
    //         mFrogger.Position().x, mFrogger.Position().y, HEADER_HEIGHT);
    // printf("%s",debug.c_str());
    // debug = std::format(" PrevX: {} PrevY: {}\n",
    //         mFrogger.PrevPosition().x, mFrogger.PrevPosition().y);
    // printf("%s",debug.c_str());

    int mFrame = 0;

    SDL_FRect mPortion;
    mPortion.x = 0 + mFrame*16;
    mPortion.y = 0;
    mPortion.h = 16;
    mPortion.w = 16;

    SDL_FRect dst;
    dst.x = 0 + (mFrog.Position().x * TILE_SIZE);
    dst.y = HEADER_HEIGHT + (mFrog.Position().y * TILE_SIZE);
    dst.h = TILE_SIZE;
    dst.w = TILE_SIZE;

    double angle = 0;

    switch (mFrog.Direction()) {
        case (UP):
            angle = 0;
            break;
        case (DOWN):
            angle = 180;
            break;
        case (LEFT):
            angle = 270;
            break;
        case (RIGHT):
            angle = 90;
    }

    if (!mFrog.IsMoving()) {

        SDL_RenderTextureRotated(renderer, textureSpriteSheet, &mPortion, &dst, angle, 
                NULL, SDL_FLIP_NONE);
    }

    else {
        mFrame = mFrog.movingFrame + 1;
        mFrog.movingFrame = mFrame;
        mPortion.x = 0 + mFrame*16;

        if (mFrog.Direction() == UP) {
            dst.x = 0 + (mFrog.PrevPosition().x * TILE_SIZE);
            dst.y = HEADER_HEIGHT + (mFrog.PrevPosition().y * TILE_SIZE) - (mFrame*(16));
        }
        else if (mFrog.Direction() == DOWN) {
            dst.x = 0 + (mFrog.PrevPosition().x * TILE_SIZE);
            dst.y = HEADER_HEIGHT + (mFrog.PrevPosition().y * TILE_SIZE) + (mFrame*(16));
        }
        else if (mFrog.Direction() == RIGHT) {
            dst.x = 0 + (mFrog.PrevPosition().x * TILE_SIZE) + (mFrame*(16));
            dst.y = HEADER_HEIGHT + (mFrog.PrevPosition().y * TILE_SIZE);
        }
        else if (mFrog.Direction() == LEFT) {
            dst.x = 0 + (mFrog.PrevPosition().x * TILE_SIZE) - (mFrame*(16));
            dst.y = HEADER_HEIGHT + (mFrog.PrevPosition().y * TILE_SIZE);
        }


        SDL_RenderTextureRotated(renderer, textureSpriteSheet, &mPortion, &dst, angle, 
                NULL, SDL_FLIP_NONE);

        if (mFrame == 3) {
            mFrog.movingFrame = 0;
            mFrog.SetIsMoving(false);

        }
    }

}


void Game::DrawCircle(int32_t game_x, int32_t game_y, bool filled, int32_t diameter)
{

    int32_t centreX =  game_x*TILE_SIZE + TILE_SIZE/2;
    int32_t centreY =  game_y*TILE_SIZE + TILE_SIZE/2;

    int32_t x = (diameter / 2 - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        if (filled)
        {
            SDL_RenderLine(renderer, centreX - x, centreY - y,
                    centreX + x, centreY - y);
            SDL_RenderLine(renderer, centreX - x, centreY + y,
                    centreX + x, centreY + y);
            SDL_RenderLine(renderer, centreX - y, centreY - x,
                    centreX + y, centreY - x);
            SDL_RenderLine(renderer, centreX - y, centreY + x,
                    centreX + y, centreY + x);
        }
        else
        {
            // Each of the following renders an octant of the circle.
            SDL_RenderPoint(renderer, centreX + x, centreY - y);
            SDL_RenderPoint(renderer, centreX + x, centreY + y);
            SDL_RenderPoint(renderer, centreX - x, centreY - y);
            SDL_RenderPoint(renderer, centreX - x, centreY + y);
            SDL_RenderPoint(renderer, centreX + y, centreY - x);
            SDL_RenderPoint(renderer, centreX + y, centreY + x);
            SDL_RenderPoint(renderer, centreX - y, centreY - x);
            SDL_RenderPoint(renderer, centreX - y, centreY + x);
        }

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

SDL_AppResult Game::AppInit() {


    SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Surface *text;

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    if(!SDL_CreateWindowAndRenderer("Frogger", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    std::filesystem::path fullPath = fontDirectory;
    fullPath /= fontBitCountGridDouble;

    std::string fontPath = fullPath.string();
    font = TTF_OpenFont(fontPath.c_str(), 22);

    if (!font) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    // setup static textures
    //
    text = TTF_RenderText_Blended(font, "Game Paused.  SPACE to continue.", 0, color); 
    if (text) {
        textureGamePaused = SDL_CreateTextureFromSurface(renderer, text);
        SDL_DestroySurface(text);
    }
    if (!textureGamePaused) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    text = TTF_RenderText_Blended(font, "Game Over.  SPACE to New Game.", 0, color); 
    if (text) {
        textureYouLost = SDL_CreateTextureFromSurface(renderer, text);
        SDL_DestroySurface(text);
    }
    if (!textureYouLost) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    text = TTF_RenderText_Blended(font, "You Won!  SPACE to New Game.", 0, color); 
    if (text) {
        textureYouWon = SDL_CreateTextureFromSurface(renderer, text);
        SDL_DestroySurface(text);
    }
    if (!textureYouWon) {
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    std::filesystem::path fullSpritesPath = spritesDirectory;
    fullSpritesPath /= "frogger.png";

    std::string spritesPath = fullSpritesPath.string();
    SDL_Surface *tmpSurface = SDL_LoadPNG(spritesPath.c_str());
    if (tmpSurface) {
        textureSpriteSheet = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_DestroySurface(tmpSurface);
    }
    if (!textureSpriteSheet) {
        SDL_Log("Couldn't create texture: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
        
    drawRect.w = drawRect.h = TILE_SIZE;
    srand(time(NULL));

    resetGame();

    ComposeScoreboardText();

    return SDL_APP_CONTINUE;

}

SDL_AppResult Game::handleAppEvent(void *, SDL_Event *event) {

    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.scancode) {
                case SDL_SCANCODE_ESCAPE:
                case SDL_SCANCODE_Q:
                    return SDL_APP_SUCCESS;
                case SDL_SCANCODE_SPACE:
                    if (isGameLost) {
                        isGameLost = false;
                        resetGame();
                    }
                    else {
                        isPaused = !isPaused;
                    }
                    break;
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    mFrog.Move(UP);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    mFrog.Move(DOWN);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    mFrog.Move(LEFT);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    mFrog.Move(RIGHT);
                    break;
                case SDL_SCANCODE_E:
                    resetGame();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::Iterate(void *) {

    if (!isPaused && !isGameLost) {
        // food logic...is snake head on food?

    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    RenderFrog();

    if (isPaused) {
        ShowPaused();
    }
    if (isGameLost) {
        ShowYouLost();
    }

    //            RenderScoreboard();

    SDL_RenderPresent(renderer);

    if(mFrog.Size() >= 200) {
        printf("You won!\n");
        resetGame();
    }
    SDL_Delay(50);
    return SDL_APP_CONTINUE;
}

