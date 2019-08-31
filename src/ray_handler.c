/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:09:54 by vmiachko          #+#    #+#             */
/*   Updated: 2019/07/21 15:09:56 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void sphere_ray_intersection(t_union *un, t_object_lst *object, t_vec viewport, t_vec canvas)
{
    float d;
    float k1;
    float k2;
    float k3;
    t_sphere *data = (t_sphere *)object->data;

    k1 = vec_dot_product(viewport, viewport);
    k2 = 2 * vec_dot_product(vec_sub(data->center, un->camera.position), viewport);
    k3 = vec_dot_product(vec_sub(data->center, un->camera.position), vec_sub(data->center, un->camera.position)) - data->radius * data->radius;

    d = k2 * k2 - 4 * k1 * k3;

    if (d >= 0)
    {
        SDL_SetRenderDrawColor(un->sdl.renderer, object->color.r, object->color.g, object->color.b, 0);
        SDL_RenderDrawPoint(un->sdl.renderer, W_WIDTH / 2 + canvas.x, W_HEIGHT / 2 - canvas.y);
    }   
}

void ray_intersection(t_union *un)
{
    t_object_lst *head = NULL;
    t_vec canvas;
    t_vec viewport;

    viewport.z = 1;
    canvas.y = -W_HEIGHT / 2;
    while (canvas.y < W_HEIGHT / 2)
    {
        canvas.x = -W_WIDTH / 2;
        while (canvas.x < W_WIDTH / 2)
        {
            head = un->lst;
            while (head)
            {
                viewport.x = canvas.x * VIEWPORT_X / (float)W_WIDTH;
                viewport.y = canvas.y * VIEWPORT_Y / (float)W_HEIGHT;
                if (head->type == SPHERE)
                    sphere_ray_intersection(un, head, viewport, canvas);
                head = head->next;
            }
            ++canvas.x;
        }
        ++canvas.y;
    }
}