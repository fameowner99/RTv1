/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:46:02 by vmiachko          #+#    #+#             */
/*   Updated: 2019/09/07 15:46:03 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int handle_events(t_union *un)
{
    if (un->sdl.event.type == SDL_QUIT)
        return (FALSE);

    while (SDL_PollEvent(&un->sdl.event))
    {
        if (un->sdl.event.type == SDL_KEYDOWN)
	    {
            if (un->sdl.event.key.keysym.sym == SDLK_ESCAPE)
                return (FALSE);
            else if (un->sdl.event.key.keysym.sym== SDLK_DOWN)
                move_camera(un, BACK);
            else if (un->sdl.event.key.keysym.sym == SDLK_UP)
                move_camera(un, FORWARD);
            else if (un->sdl.event.key.keysym.sym == SDLK_LEFT)
                move_camera(un, LEFT);
            else if (un->sdl.event.key.keysym.sym == SDLK_RIGHT)
                move_camera(un, RIGHT);
        }
        else if (un->sdl.event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (un->sdl.event.button.button == SDL_BUTTON_RIGHT)
            {
                un->mouse.is_clicked = TRUE;
                SDL_GetMouseState(&un->mouse.clicked_x, &un->mouse.clicked_y);
            }
        }
        else if (un->sdl.event.type == SDL_MOUSEBUTTONUP)
        {
            if (un->sdl.event.button.button == SDL_BUTTON_RIGHT)
            {
                un->mouse.is_clicked = FALSE;
                rotate_camera(un);
            }
        }
        else if (un->sdl.event.type == SDL_MOUSEMOTION)
        {
        }
    }

    return (TRUE);
}