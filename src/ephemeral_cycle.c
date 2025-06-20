#include "SDL3_image/SDL_image.h"
#include "lifecycle.h"
#include "shared.h"

SDLWindow* window;
SDLRenderer* renderer;
Bool running = true;

U0 cycleStart()
{
    setAppMetadata(APP_NAME, APP_VERSION, APP_GROUP_NAME);
    window = createWindow(APP_NAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(window == null)
    {
        printerr("Failed to create window: %s", sdl_getError());
        sdl_quit();
        exit(1);
    }
    setWindowFocusable(window, true);
    SDLSurface* windowIcon = IMG_Load(".\\assets\\logo.png");
    if(windowIcon == null)
    {
        printerr("Couldn't find window icon (it's ok): %s", sdl_getError());
    }
    if(!SDL_SetWindowIcon(window, windowIcon))
    {
        printerr("Failed to set window icon (it's ok): %s", sdl_getError());
    }
    if(!sdl_init(SDL_INIT_VIDEO))
    {
        printerr("Couldn't initialize SDL: %s", sdl_getError());
        exit(1);
    }
    renderer = createRenderer(window, null);
    if(renderer == null)
    {
        printerr("Failed to create renderer: %s", sdl_getError());
        destroyWindow(window);
        sdl_quit();
        exit(1);
    }
}

U0 cycleEnd()
{
    destroyRenderer(renderer);
    destroyWindow(window);
    renderer = null;
    window = null;
    sdl_quit();
}