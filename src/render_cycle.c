#include <math.h>

#include "lifecycle.h"
#include "public.h"
#include "colors.h"
#include "extras_math.h"

F32 posX = MAP_WIDTH / 2;
F32 posY = MAP_HEIGHT / 2;
F32 dirX = -1.f;
F32 dirY = 0.f;
F32 planeX = 0.f;
F32 planeY = 0.66f;
F32 moveSpeed = 0.56f;
F32 rotSpeed = 0.046f;

I32 getWallColor(I16 cellValue, I32 side, F32 perpWallDist)
{
    implyUsed(side);
    F32 factor = clampF32(1.0f - (perpWallDist / 20.0f), 0.f, 1.f);
    I32 baseColor;
    switch(S_GET_ID(cellValue))
    {
        case 1:
            baseColor = COLOR_BLUE;
            break;
        case 2:
            baseColor = COLOR_RED;
            break;
        case 3:
            baseColor = COLOR_GREEN;
            break;
        default:
            return COLOR_MAGENTA;
    }
    // out of distance objects will render as a grayscaled very darkened version
    // additionally, too close objects are also clamped to a max value (this also reserves for potentially glowing objects)
    return (((I32) (clampU8(((baseColor >> 24) & 0xFF) * factor, 1, 170))) << 24) |
           (((I32) (clampU8(((baseColor >> 16) & 0xFF) * factor, 1, 170))) << 16) |
           (((I32) (clampU8(((baseColor >> 8) & 0xFF) * factor, 1, 170))) << 8) |
           (baseColor & 0xFF);
}

SDLEvent eventPipe;

U0 draw()
{
    while(running)
    {
        while(pollSDLEvent(&eventPipe))
        {
            update();
        }
        if(!running)
        {
            break;
        }
        setDrawColor(renderer, COLOR_BLACK);
        clearRender(renderer);
        for(I32 x = 0; x < SCREEN_WIDTH; x++)
        {
            F32 cameraX = 2 * x / (F32) SCREEN_WIDTH - 1;
            F32 rayDirX = dirX + planeX * cameraX;
            F32 rayDirY = dirY + planeY * cameraX;
            I32 mapX = (I32) posX;
            I32 mapY = (I32) posY;
            F32 sideDistX;
            F32 sideDistY;
            F32 deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            F32 deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
            F32 perpWallDist;
            I32 stepX;
            I32 stepY;
            Bool hit = false;
            // ----------------------------------------------------------------
            // used to indicate on whether it is horizontal or a vertical wall
            //
            // - a vertical wall is defined as a north-south facing wall
            // - a horizontal wall is define as a east-west facing wall
            // ----------------------------------------------------------------
            I32 side;
            I16 cellValue;
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
            while(!hit)
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
                cellValue = worldMap[mapX][mapY];
                if (!S_CAN_PASSTHROUGH(cellValue))
                {
                    hit = true;
                }
            }
            perpWallDist = side == 0
                                ? (mapX - posX + (1 - stepX) / 2) / rayDirX
                                : (mapY - posY + (1 - stepY) / 2) / rayDirY;
            I32 lineHeight = (I32) (SCREEN_HEIGHT / perpWallDist);
            I32 drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if(drawStart < 0)
            {
                drawStart = 0;
            }
            I32 drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if(drawEnd >= SCREEN_HEIGHT)
            {
                drawEnd = SCREEN_HEIGHT - 1;
            }
            setDrawColor(renderer, getWallColor(cellValue, side, perpWallDist));
            drawLine(renderer, x, drawStart, x, drawEnd);
            setDrawColor(renderer, COLOR_BLACK);
            drawLine(renderer, x, 0, x, drawStart);
            setDrawColor(renderer, COLOR_BLACK);
            drawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT - 1);
        }
        setDrawColor(renderer, COLOR_GREEN);
        I8 playerPosStr[128];
        snprintf(playerPosStr, sizeof(playerPosStr), "Pos: X=%.2f, Y=%.2f\nAngle=%.2f", posX, posY, atan2(dirY, dirX) * RAD2DEG);
        drawDebugText(renderer, 16, 16, playerPosStr);
        flushRender(renderer);
        presentRender(renderer);
        sdl_delay(42);
    }
}