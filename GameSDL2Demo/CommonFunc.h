#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Music *gMusic = NULL;

const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xFF;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 150
#define MAX_MAP_Y 10

#define PLAY_TIME 300

#define CHECK_POINT 17
#define STATE_MONEY 21
#define STATE_TRAP 18 //19 20
#define STATE_HEAL 23
#define MAX_BULLET 100
#define STATE_WINGAME 22

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name_;
};


namespace SDLCommonFunc
{
    bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);
};

enum menuOption
{
    START = 100,
    PLAY = 101,
    PAUSE = 102,
    END = 103,
    INFO = 104,
    WIN = 105,
};
static int bullet_in_gun = 0;

#endif // COMMON_FUNCTION_H_
