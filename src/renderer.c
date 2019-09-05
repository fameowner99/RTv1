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

void draw_on_canvas(t_union *un, t_object_lst *object, t_vec canvas)
{
    if (!object)
        SDL_SetRenderDrawColor(un->sdl.renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, 0);
    else
        SDL_SetRenderDrawColor(un->sdl.renderer, object->color.r, object->color.g, object->color.b, 0);
    SDL_RenderDrawPoint(un->sdl.renderer, W_WIDTH / 2 + canvas.x, W_HEIGHT / 2 - canvas.y);
}

void draw(t_union *un)
{
    ray_intersection(un);
}