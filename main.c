#define SDL_MAIN_USE_CALLBACKS 0
#define JM_REDEFINE_SDL_TYPES
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <math.h>

#include "SDL3/SDL.h"
#include "def.h"
#include "shared.h"
#include "colors.h"
#include "extras_math.h"

static const I32 worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static F32 posX = 22.f;
static F32 posY = 11.f;
static F32 dirX = -1.f;
static F32 dirY = 0.f;
static F32 planeX = 0.f;
static F32 planeY = 0.66f;
static F32 moveSpeed = 0.56f;
static F32 rotSpeed = 0.046f;

static SDLWindow* window = null;
static SDLRenderer* renderer = null;
static Bool running = true;

U16 getWallColor(I32 side, F32 perpWallDist) {
    F32 factor = 1.0f - (perpWallDist / 20.0f);
    if (factor < 0.f) factor = 0.f;
    if (factor > 1.f) factor = 1.f;
    U8 r, g, b;
    if (side == 0)
    {
        r = 255;
        g = (U8) (255 * factor);
        b = 255;
    }
    else
    {
        r = (U8) (255 * factor);
        g = (U8) (255 * factor);
        b = 255;
    }
    return ((r & 0xF8) << 8) |
           ((g & 0xFC) << 3) |
           ((b & 0xF8) >> 3);
}

#define KEY_ARROW_LEFT (1)
#define KEY_ARROW_RIGHT (1 << 1)
#define KEY_ARROW_UP  (1 << 2)
#define KEY_ARROW_DOWN (1 << 3)

U0 justDrawIt()
{
    SDLEvent event;
    U8 keysMask = 0;
    while(pollSDLEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
        {
            running = false;
        }
        else if(event.type == SDL_EVENT_KEY_DOWN)
        {
            if(event.key.key == SDLK_UP)
            {
                keysMask |= KEY_ARROW_UP;
                if(worldMap[(I32)(posX + dirX * moveSpeed)][(I32)posY] == 0)
                {
                    posX += dirX * moveSpeed;
                }
                if(worldMap[(I32)posX][(I32)(posY + dirY * moveSpeed)] == 0)
                {
                    posY += dirY * moveSpeed;
                }
            }
            else if(event.key.key == SDLK_DOWN)
            {
                keysMask |= KEY_ARROW_DOWN;
                if(worldMap[(I32)(posX - dirX * moveSpeed)][(I32)posY] == 0)
                {
                    posX -= dirX * moveSpeed;
                }
                if(worldMap[(I32)posX][(I32)(posY - dirY * moveSpeed)] == 0)
                {
                    posY -= dirY * moveSpeed;
                }
            }
            if(event.key.key == SDLK_LEFT)
            {
                keysMask |= KEY_ARROW_LEFT;
                dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                dirY = dirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                F32 oldPlaneX = planeX;
                planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
            }
            else if(event.key.key == SDLK_RIGHT)
            {
                keysMask |= KEY_ARROW_RIGHT;
                dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                dirY = dirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                F32 oldPlaneX = planeX;
                planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
            }
        }
    }
    setDrawColor16(renderer, COLOR_BLACK);
    clearRender(renderer);
    for(I32 x = 0; x < SCREEN_WIDTH; x++)
    {
        F32 cameraX = 2 * x / (F32) SCREEN_WIDTH - 1;
        F32 rayDirX = dirX + planeX * cameraX;
        F32 rayDirY = dirY + planeY * cameraX;
        I32 mapX = (I32)posX;
        I32 mapY = (I32)posY;
        F32 sideDistX;
        F32 sideDistY;
        F32 deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        F32 deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        F32 perpWallDist;
        I32 stepX;
        I32 stepY;
        I32 hit = 0;
        I32 side;
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        while(hit == 0)
        {

            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        perpWallDist = side == 0
                            ? (mapX - posX + (1 - stepX) / 2) / rayDirX
                            : (mapY - posY + (1 - stepY) / 2) / rayDirY;
        I32 lineHeight = (I32)(SCREEN_HEIGHT / perpWallDist);
        I32 drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(drawStart < 0) drawStart = 0;
        I32 drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(drawEnd >= SCREEN_HEIGHT)
        {
            drawEnd = SCREEN_HEIGHT - 1;
        }
        setDrawColor16(renderer, getWallColor(side, perpWallDist));
        drawLine(renderer, x, drawStart, x, drawEnd);
        setDrawColor16(renderer, COLOR_WHITE); // ceiling color
        drawLine(renderer, x, 0, x, drawStart);
        setDrawColor16(renderer, COLOR_WHITE); // floor color
        drawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT - 1);
    }
    flushRender(renderer);
    presentRender(renderer);
}

I32 main(I32 argc, I8** argv)
{
    (U0) argc;
    (U0) argv;
    setAppMetadata(APP_NAME, APP_VERSION, APP_GROUP_NAME);
    if(!sdl_init(SDL_INIT_VIDEO))
    {
        printerr("Couldn't initialize SDL: %s", sdl_getError());
        return 1;
    }
    window = createWindow(APP_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    setWindowFocusable(window, true);
    if(window == null)
    {
        printerr("Failed to create window: %s", sdl_getError());
        sdl_quit();
        return 1;
    }
    renderer = createRenderer(window, null);
    if(renderer == null)
    {
        printerr("Failed to create renderer: %s", sdl_getError());
        destroyWindow(window);
        sdl_quit();
        return 1;
    }
    while(running)
    {
        justDrawIt();
    }
    destroyRenderer(renderer);
    destroyWindow(window);
    renderer = null;
    window = null;
    sdl_quit();
    return 0;
}