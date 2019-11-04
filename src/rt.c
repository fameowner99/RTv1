
#include "rtv1.h"

int init_sld(t_union *un)
{
     if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return (FALSE);

    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &un->sdl.window, &un->sdl.renderer);

    return (TRUE);
}

void rt(t_union *un)
{
    Uint32       start;
    int          is_running;

    if (!init_sld(un))
        exit(666);
       // ft_printf("Error happend during SDL initialization.\n");

    draw(un);
    is_running = TRUE;
    while (is_running)
    {
        is_running = handle_events(un);
        start = SDL_GetTicks();
        if (1000 / FPS > SDL_GetTicks() - start)
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }

    }

    SDL_DestroyRenderer(un->sdl.renderer);
    SDL_DestroyWindow(un->sdl.window);
    SDL_Quit();
}