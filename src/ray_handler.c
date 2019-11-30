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

    solve.t1 = INF;
    solve.t2 = INF;
    d = k2 * k2 - 4 * k1 * k3;
    if (d < 0)
        return (solve);
    solve.t1 = (-k2 - sqrt(d)) / (2. * k1);
    solve.t2 = (-k2 + sqrt(d)) / (2. * k1);
    return (solve);
}

t_vec canvas_to_viewport(t_vec canvas)
{
    t_vec viewport;

    viewport.x = canvas.x * VIEWPORT_X / (float)W_WIDTH;
    viewport.y = canvas.y * VIEWPORT_Y / (float)W_HEIGHT;
    return (viewport);
}

t_equation_solve sphere_ray_intersection(t_union *un, t_object *object, t_vec direction, t_vec start_point)
{
    float k1;
    float k2;
    float k3;
    t_sphere *data;

    data = (t_sphere *)object->data;
    k1 = vec_dot_product(direction, direction);
    k2 = 2 * vec_dot_product(vec_sub(start_point, data->center), direction);
    k3 = vec_dot_product(vec_sub(start_point, data->center), vec_sub(start_point, data->center)) - data->radius * data->radius;

    return (solve_equation(un, k1, k2, k3));
}

t_equation_solve plane_ray_intersection(t_union *un, t_object *object, t_vec direction, t_vec start_point)
{
    t_equation_solve solve;
    t_plane *data;

    data = (t_plane *)object->data;
    solve.t2 = INF;
    solve.t1 = -vec_dot_product(vec_sub(start_point, data->center), data->normal) /  vec_dot_product(direction, data->normal);
    return (solve);
}

t_equation_solve cylinder_ray_intersection(t_union *un, t_object *object, t_vec direction, t_vec start_point)
{
    t_cylinder *data;
    float k1;
    float k2;
    float k3;
    t_vec center_pos;

    data = (t_cylinder *)object->data;
    center_pos = vec_add(data->cap, vec_mul(data->axis, data->max / 2));
    k1 = vec_dot_product(direction, direction) - vec_dot_product(direction, data->axis) * vec_dot_product(direction, data->axis);
    k2 = 2 * (vec_dot_product(vec_sub(start_point, center_pos), direction) - vec_dot_product(direction, data->axis) * vec_dot_product(vec_sub(start_point, center_pos), data->axis));
    k3 = vec_dot_product(vec_sub(start_point, center_pos), vec_sub(start_point, center_pos)) -
        vec_dot_product(vec_sub(start_point, center_pos), data->axis) * vec_dot_product(vec_sub(start_point, center_pos), data->axis) - data->r * data->r;
    return (solve_equation(un, k1, k2, k3));
}

t_equation_solve cone_ray_intersection(t_union *un, t_object *object, t_vec direction, t_vec start_point)
{
    t_cone *data;
    float k1;
    float k2;
    float k3;
    t_vec center_pos;

    data = (t_cone *)object->data;
    center_pos = vec_add(data->vertex, vec_mul(data->axis, data->min + (data->max - data->min) / 2));
    k1 = vec_dot_product(direction, direction) - (1 + data->tg * data->tg) * vec_dot_product(direction, data->axis) * vec_dot_product(direction, data->axis);
    k2 = 2 * (vec_dot_product(direction, vec_sub(start_point, center_pos)) - (1 + data->tg * data->tg) * vec_dot_product(direction, data->axis) * vec_dot_product(vec_sub(start_point, center_pos), data->axis));
    k3 = vec_dot_product(vec_sub(start_point, center_pos), vec_sub(start_point, center_pos)) - (1 + data->tg * data->tg) * vec_dot_product(vec_sub(start_point, center_pos), data->axis) * vec_dot_product(vec_sub(start_point, center_pos), data->axis);
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

t_color get_closest_object_color(t_union *un, t_vec viewport)
{
    t_object *object;
    t_object *closest_object;
    float closest_root;
    t_equation_solve solve;

    solve.t1 = INF;
    solve.t2 = INF;
    object = un->objects;
    closest_object = NULL;
    closest_root = INF;
    while (object)
    {
        if (object->type == SPHERE)
            solve = sphere_ray_intersection(un, object, viewport, un->camera.basis.position);
        else if (object->type == PLANE)
            solve = plane_ray_intersection(un, object, viewport, un->camera.basis.position);
        else if (object->type == CYLINDER)
            solve = cylinder_ray_intersection(un, object, viewport, un->camera.basis.position);
        else if (object->type == CONE)
            solve = cone_ray_intersection(un, object, viewport, un->camera.basis.position);
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
    return (get_color_with_light(un, closest_object, closest_root, viewport));
}

void ray_intersection(t_union *un)
{
    t_color color;
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
            color = get_closest_object_color(un, viewport);
            draw_on_canvas(un, color, canvas);
            ++canvas.x;
        }
        ++canvas.y;
    }
}