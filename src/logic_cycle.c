#include <math.h>

#include "lifecycle.h"
#include "public.h"

U0 update()
{
    U8 keysMask = 0;
    if(eventPipe.type == SDL_EVENT_QUIT)
    {
        running = false;
    }
    else if(eventPipe.type == SDL_EVENT_KEY_DOWN)
    {
        if(eventPipe.key.key == SDLK_W)
        {
            keysMask |= AX_MOVE_UP;
            if(S_CAN_PASSTHROUGH(worldMap[(I32) (posX + dirX * moveSpeed)][(I32) posY]))
            {
                posX += dirX * moveSpeed;
            }
            if(S_CAN_PASSTHROUGH(worldMap[(I32) posX][(I32) (posY + dirY * moveSpeed)]))
            {
                posY += dirY * moveSpeed;
            }
        }
        else if(eventPipe.key.key == SDLK_S)
        {
            keysMask |= AX_MOVE_DOWN;
            if(S_CAN_PASSTHROUGH(worldMap[(I32) (posX - dirX * moveSpeed)][(I32) posY]))
            {
                posX -= dirX * moveSpeed;
            }
            if(S_CAN_PASSTHROUGH(worldMap[(I32) posX][(I32)(posY - dirY * moveSpeed)]))
            {
                posY -= dirY * moveSpeed;
            }
        }
        if(eventPipe.key.key == SDLK_A)
        {
            keysMask |= AX_MOVE_LEFT;
            F32 oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            F32 oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        else if(eventPipe.key.key == SDLK_D)
        {
            keysMask |= AX_MOVE_RIGHT;
            F32 oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            F32 oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
    }
}