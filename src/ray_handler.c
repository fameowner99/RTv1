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


t_equation_solve solve_equation(float k1, float k2, float k3)
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

t_equation_solve sphere_ray_intersection(t_object *object, t_vec direction, t_vec start_point)
{
    float k1;
    float k2;
    float k3;
    t_sphere *data;

    data = (t_sphere *)object->data;
    k1 = vec_dot_product(direction, direction);
    k2 = 2 * vec_dot_product(vec_sub(start_point, data->center), direction);
    k3 = vec_dot_product(vec_sub(start_point, data->center), vec_sub(start_point, data->center)) - data->radius * data->radius;

    return (solve_equation(k1, k2, k3));
}

t_equation_solve plane_ray_intersection(t_object *object, t_vec direction, t_vec start_point)
{
    t_equation_solve solve;
    t_plane *data;

    data = (t_plane *)object->data;
    solve.t2 = INF;
    solve.t1 = -vec_dot_product(vec_sub(start_point, data->center), data->normal) /  vec_dot_product(direction, data->normal);
    return (solve);
}

t_equation_solve 	polygon_ray_intersection(t_object *object, t_vec direction, t_vec start_point)
{
    t_equation_solve solve;
    t_polygon *data;
    t_vec v0, p0;
    t_vec v1, p1;
    t_vec v2, p2;
    int i = 0;
    float t = INF;

    data = (t_polygon*)object->data;
    solve.t2 = INF;
    while (i < data->vertices_size)
    {
        vec_set(&v0, data->vertices[i], data->vertices[i + 1], data->vertices[i + 2]);
        vec_set(&v1, data->vertices[i + 3], data->vertices[i + 4], data->vertices[i + 5]);
        vec_set(&v2, data->vertices[i + 6], data->vertices[i + 7], data->vertices[i + 8]);
        solve = triangle_ray_intersection(v0, v1, v2, direction, start_point);
        if (solve.t1 < t)
        {
            t = solve.t1;
            vec_set_v(&p0, v0);
            vec_set_v(&p1, v1);
            vec_set_v(&p2, v2);
        }
        else if (solve.t2 < t)
        {
            t = solve.t2;
            vec_set_v(&p0, v0);
            vec_set_v(&p1, v1);
            vec_set_v(&p2, v2);
        }
        i += 9;
    }
    solve.t1 = t;
    solve.t2 = INF;

    if (solve.t1 > 1 && solve.t1 < INF)
    {
        t_vec u = vec_sub(p1, p0);
        t_vec v = vec_sub(p2, p1);

        data->intersected_triangle_normal = vec_cross_product(u, v);
    }

    return (solve);
}
#define MOLLER_TRUMBORE
t_equation_solve 	triangle_ray_intersection(t_vec v0, t_vec v1, t_vec v2, t_vec direction, t_vec start_point)
{
    t_vec e1 = vec_sub(v1, v0);
    t_vec e2 = vec_sub(v2, v0);
    // Calculation of the normal vector to the plane
    t_vec pvec = vec_cross_product(direction, e2);
    float det = vec_dot_product(e1, pvec);
    t_equation_solve solve;
    solve.t1 = INF;
    solve.t2 = INF;
    // The ray is parallel to the plane
    if (det < 1e-8 && det > -1e-8) {
        return solve;
    }

    float inv_det = 1 / det;
    t_vec tvec = vec_sub(start_point, v0);
    float u = vec_dot_product(tvec, pvec)  * inv_det;
    if (u < 0 || u > 1) {
        return solve;
    }

    t_vec qvec = vec_cross_product(tvec, e1);
    float v = vec_dot_product(direction, qvec)  * inv_det;
    if (v < 0 || u + v > 1) {
        return solve;
    }
    solve.t1 = vec_dot_product(e2, qvec) * inv_det;
    return solve;
}

t_equation_solve cylinder_ray_intersection(t_object *object, t_vec direction, t_vec start_point)
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
        vec_dot_product(vec_sub(start_point, center_pos), data->axis) * vec_dot_product(vec_sub(start_point, center_pos), data->axis) - data->radius * data->radius;
    return (solve_equation(k1, k2, k3));
}

t_equation_solve cone_ray_intersection(t_object *object, t_vec direction, t_vec start_point)
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
    return (solve_equation(k1, k2, k3));
}


int is_root_valid(float root, float closest_root, t_object *closest_object)
{
    if (root >= INF || root <= PROJECTION_PLANE_DISTANCE)
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
            solve = sphere_ray_intersection(object, viewport, un->camera.basis.position);
        else if (object->type == PLANE)
            solve = plane_ray_intersection(object, viewport, un->camera.basis.position);
        else if (object->type == CYLINDER)
            solve = cylinder_ray_intersection(object, viewport, un->camera.basis.position);
        else if (object->type == CONE)
        	solve = cone_ray_intersection(object, viewport, un->camera.basis.position);
        else if (object->type == POLYGON)
            solve = polygon_ray_intersection(object, viewport, un->camera.basis.position);

        if (is_root_valid(solve.t1, closest_root, closest_object))
        {
            closest_object = object;
            closest_root = solve.t1;
        }
        if (is_root_valid(solve.t2, closest_root, closest_object))
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
            viewport.z = PROJECTION_PLANE_DISTANCE;
            color = get_closest_object_color(un, apply_rotate_matrix(viewport, &un->camera.matrix));
            draw_on_canvas(un, color, canvas);
            ++canvas.x;
        }
        ++canvas.y;
    }
}