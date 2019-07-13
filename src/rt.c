
#include "rtv1.h"

void rt(t_union *un)
{
    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &un->sdl.window, &un->sdl.renderer);
    SDL_RenderClear(un->sdl.renderer);
    SDL_SetRenderDrawColor(un->sdl.renderer, 0, 0, 0, 0);
    Uint32       start;

     while (TRUE)
     {
        //SDL_RenderClear(un->sdl.renderer);
        if (SDL_PollEvent(&un->sdl.event) && (un->sdl.event.type == SDL_QUIT || un->sdl.event.key.keysym.sym == SDLK_ESCAPE))
            break;
        start = SDL_GetTicks();

        //SDL_SetRenderDrawColor(un->sdl.renderer, 0, 0, 0, 0);
       // SDL_RenderPresent(un->sdl.renderer);
        //SDL_UpdateWindowSurface(un->sdl.window);

        /*if (1000 / FPS > SDL_GetTicks() - start)
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }*/

     }

    SDL_DestroyRenderer(un->sdl.renderer);
    SDL_DestroyWindow(un->sdl.window);
    SDL_Quit();
}