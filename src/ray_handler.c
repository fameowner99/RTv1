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


t_equation_solve solve_equation(t_union *un, float k1, float k2, float k3)
{
    float d;
    t_equation_solve solve;

    solve.t1 = un->camera.basis.position.z - 1;
    solve.t2 = un->camera.basis.position.z - 1;
    d = k2 * k2 - 4 * k1 * k3;
    if (d < 0)
        return (solve);
    solve.t1 = -k2 - sqrt(d) / (2 * k1);
    solve.t2 = -k2 + sqrt(d) / (2 * k1);
    return (solve);
}

t_vec canvas_to_viewport(t_vec canvas)
{
    t_vec viewport;

    viewport.x = canvas.x * VIEWPORT_X / (float)W_WIDTH;
    viewport.y = canvas.y * VIEWPORT_Y / (float)W_HEIGHT;
    return (viewport);
}

t_equation_solve sphere_ray_intersection(t_union *un, t_object *object, t_vec viewport, t_vec canvas)
{
    float k1;
    float k2;
    float k3;
    t_sphere *data = (t_sphere *)object->data;

    k1 = vec_dot_product(viewport, viewport);
    k2 = 2 * vec_dot_product(vec_sub(un->camera.basis.position, data->center), viewport);
    k3 = vec_dot_product(vec_sub(un->camera.basis.position, data->center), vec_sub(un->camera.basis.position, data->center)) - data->radius * data->radius;

    return (solve_equation(un, k1, k2, k3));
}

int is_root_valid(t_union *un, float root, float closest_root, t_object *closest_object)
{
    if (root < un->camera.projection_plane_distance)
        return (FALSE);
    if (closest_object)
    {
        if (root < closest_root)
            return (TRUE);
    }
    else
        return (TRUE);
    return (FALSE);
}

t_object *get_closest_object(t_union *un, t_vec viewport, t_vec canvas)
{
    t_object *object;
    t_object *closest_object;
    float closest_root;
    t_equation_solve solve;

    solve.t1 = un->camera.basis.position.z - 1;
    solve.t2 = un->camera.basis.position.z - 1;
    object = un->lst;
    closest_object = NULL;
    while (object)
    {
        if (object->type == SPHERE)
            solve = sphere_ray_intersection(un, object, viewport, canvas);
        if (is_root_valid(un, solve.t1, closest_root, closest_object))
        {
            closest_object = object;
            closest_root = solve.t1;
        }
        if (is_root_valid(un, solve.t2, closest_root, closest_object))
        {
            closest_object = object;
            closest_root = solve.t2;
        }
        object = object->next;
    }
    return (closest_object);
}

void ray_intersection(t_union *un)
{
    t_object *closest_object;
    t_vec canvas;
    t_vec viewport;
  
    canvas.y = -W_HEIGHT / 2;
    while (canvas.y < W_HEIGHT / 2)
    {
        canvas.x = -W_WIDTH / 2;
        while (canvas.x < W_WIDTH / 2)
        {
            viewport = canvas_to_viewport(canvas);
            viewport.z = un->camera.projection_plane_distance;
            closest_object = get_closest_object(un, viewport, canvas);
            draw_on_canvas(un, closest_object, canvas);
            ++canvas.x;
        }
        ++canvas.y;
    }
}