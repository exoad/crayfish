#ifndef __JM_LIFECYCLE_H__
#define __JM_LIFECYCLE_H__
#include "def.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define AX_MOVE_LEFT (1 << 0)
#define AX_MOVE_RIGHT (1 << 1)
#define AX_MOVE_UP  (1 << 2)
#define AX_MOVE_DOWN (1 << 3)

extern SDLWindow* window;
extern SDLRenderer* renderer;
extern Bool running;
extern SDLEvent eventPipe;

extern F32 posX;
extern F32 posY;
extern F32 dirX;
extern F32 dirY;
extern F32 planeX;
extern F32 planeY;
extern F32 moveSpeed;
extern F32 rotSpeed;

U0 cycleStart();

U0 cycleEnd();

U0 draw();

U0 update();

#endif