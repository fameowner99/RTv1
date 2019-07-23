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


void sphere_ray_intersection(t_union *un, t_object_lst *object, t_vec v, int x, int y)
{
    float d;
    float k1;
    float k2;
    float k3;
    t_sphere *data = (t_sphere *)object->data;

    k1 = vec_dot_product(v, v);
    k2 = 2 * vec_dot_product(data->center,v);
    k3 = vec_dot_product(data->center, data->center) - data->radius * data->radius;

    d = k2 * k2 - 4 * k1 * k3;

    if (d >= 0)
    {
        SDL_SetRenderDrawColor(un->sdl.renderer, object->color.r, object->color.g, object->color.b, 0);
    }
    else
    {
        SDL_SetRenderDrawColor(un->sdl.renderer, 0, 0, 0, 0);
       
    }
    SDL_RenderDrawPoint(un->sdl.renderer, x + W_WIDTH / 2, y + W_HEIGHT / 2);
}

void ray_intersection(t_union *un)
{
    t_object_lst *head = NULL;
    t_vec v;
    int x;
    int y;

    y = -W_HEIGHT / 2;
    while (y < W_HEIGHT / 2)
    {
        x = -W_WIDTH / 2;
        while (x < W_WIDTH / 2)
        {
            head = un->lst;
            while (head)
            {
                v.x = x;
                v.y = y;
                v.z = 500;
                if (head->type == SPHERE)
                    sphere_ray_intersection(un, head, v, x ,y);

                head = head->next;
            }
            ++x;
        }
        ++y;
    }
}