
#include "rtv1.h"

int init_sld(t_union *un)
{
     if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return (FALSE);

    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &un->sdl.window, &un->sdl.renderer);

    return (TRUE);
}


/*void change_objects_position(t_union *un)
{
	t_object *obj =  un->objects;
	static int i = 0;
	static int sign = 1;
	if (i == 10)
	{
		i = 0;
		sign = -sign;
	}
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			t_sphere *sphere = obj->data;
			sphere->center.x += 0.5 * sign;
			sphere->center.z += 0.5 * sign;
		}
		else if (obj->type == CONE)
		{
			t_cone *cone = obj->data;
			cone->vertex.x += 0.5 * sign;
			cone->vertex.y += 0.5 * sign;
			cone->vertex.z += 0.5 * sign;

		}

		obj = obj->next;
	}
	++i;
}*/


void rt(t_union *un)
{
    Uint32       start;
    int          is_running;

    if (!init_sld(un))
    {
		ft_printf("Error happend during SDL initialization.\n");
		exit(666);
	}


	draw(un);
    is_running = TRUE;
    while (is_running)
    {
	//	change_objects_position(un);
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