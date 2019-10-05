/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:07:30 by vmiachko          #+#    #+#             */
/*   Updated: 2019/07/21 15:07:33 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void draw_on_canvas(t_union *un, t_color color, t_vec canvas)
{
    SDL_SetRenderDrawColor(un->sdl.renderer, color.r, color.g, color.b, 0);
    SDL_RenderDrawPoint(un->sdl.renderer, W_WIDTH / 2 + canvas.x, W_HEIGHT / 2 - canvas.y);
}

void draw(t_union *un)
{
    SDL_RenderClear(un->sdl.renderer);

    ray_intersection(un);

    SDL_SetRenderDrawColor(un->sdl.renderer, 0, 0, 0, 0);
    SDL_RenderPresent(un->sdl.renderer);
}