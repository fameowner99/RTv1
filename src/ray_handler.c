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

    k1 = vec_dot_product(vec_sub(v, un->camera.position), vec_sub(v, un->camera.position));
    k2 = 2 * vec_dot_product(vec_sub(un->camera.position, data->center), vec_sub(v, un->camera.position));
    k3 = vec_dot_product(vec_sub(un->camera.position, data->center), vec_sub(un->camera.position, data->center)) - data->radius * data->radius;

    d = k2 * k2 - 4 * k1 * k3;

    if (d >= 0)
    {
        SDL_SetRenderDrawColor(un->sdl.renderer, 169, 169, 169, 0);
    }
    else
    {
        SDL_SetRenderDrawColor(un->sdl.renderer, 0, 0, 0, 0);
       
    }
    SDL_RenderDrawPoint(un->sdl.renderer, x, y);
}

void ray_intersection(t_union *un)
{
    t_object_lst *head = NULL;
    t_vec v;
    int x;
    int y;

    y = -250;
    while (y < 500)
    {
        x = -250;
        while (x < 500)
        {
            head = un->lst;
            while (head)
            {
                v.x = x * W_WIDTH / 500;
                v.y = y * W_HEIGHT / 500;
                v.z = 1;
                if (head->type == SPHERE)
                    sphere_ray_intersection(un, head, v, x ,y);

                head = head->next;
            }
            ++x;
        }
        ++y;
    }
}