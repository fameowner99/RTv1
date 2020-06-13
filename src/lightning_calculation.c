/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning_calculation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:13:37 by vmiachko          #+#    #+#             */
/*   Updated: 2019/10/05 17:13:39 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			is_lit(t_union *un, t_vec point, t_vec light_position)
{
	t_object *object;
	t_equation_solve solve;
	t_vec direction;

	solve.t1 = INF;
	solve.t2 = INF;

	direction = vec_sub(light_position, point);
	object = un->objects;

	while (object)
	{
		if (object->type == SPHERE)
			solve = sphere_ray_intersection(object, direction, point);
		else if (object->type == PLANE)
			solve = plane_ray_intersection(object, direction, point);
		else if (object->type == CYLINDER)
			solve = cylinder_ray_intersection(object, direction, point);
		else if (object->type == CONE)
			solve = cone_ray_intersection(object, direction, point);

		if ((solve.t1 >= 0.001f && solve.t1 <= 1)
			|| (solve.t2 >= 0.001f && solve.t2 <= 1))
			return (FALSE);
		object = object->next;}
	return (TRUE);
}

float       get_intensity(t_union *un, t_vec normal, t_vec point, t_vec direction, int specular)
{
    t_light *light;
    t_vec    l;
    t_vec	 r;
    float   intensity;
    float   cos_alpha;
    float 	cos_beta;

    intensity = 0;
    light = un->lights;
    while (light)
    {
        if (light->type == AMBIENT)
            intensity += light->intensity;
        else if (light->type == POINT)
        {
            l = vec_sub(light->position, point);
            if (is_lit(un, point, light->position))
            {
				cos_alpha = vec_dot_product(vec_unit(l), normal);
				r = vec_sub(vec_mul(normal, 2 * vec_dot_product(normal, l)), l);
				cos_beta = vec_dot_product(vec_unit(r), vec_unit(direction));

				if (specular > 0 && cos_beta > 0)
					intensity += pow(cos_beta, specular) * light->intensity;
				if (cos_alpha > 0)
					intensity += cos_alpha * light->intensity;
			}
        }
        light = light->next;
    }
    return (intensity > 1 ? 1 : intensity);
}

t_vec      get_normal(t_object *object, t_vec point, t_vec viewport, float closest_root, t_union *un)
{
    if (object->type == SPHERE)
        return (get_normal_sphere(object, point));
    else if (object->type == PLANE)
        return (get_normal_plane(object, point));
    else if (object->type == CYLINDER)
        return (get_normal_cylinder(object, point, viewport, closest_root, un));
    else if (object->type == CONE)
        return (get_normal_cone(object, point, viewport, closest_root, un));
    else if (object->type == POLYGON)
        return (((t_polygon*)object)->intersected_triangle_normal);
    ft_printf(RED"Unknown object\n"RESET);
    exit(666);       
}

t_color	    get_color_with_light(t_union *un, t_object *closest_object, float closest_root, t_vec viewport)
{
    t_color result_color;
    float   intensity;
    t_vec   point;

    if (!closest_object)
        return g_background_color;
    point =  vec_add(un->camera.basis.position, vec_mul(vec_unit(viewport), closest_root));
    intensity = get_intensity(un, get_normal(closest_object, point, viewport, closest_root, un), point,
    		vec_unit(vec_sub(un->camera.basis.position, viewport)), closest_object->material.specular);
    result_color.r = (uint8_t)(closest_object->material.color.r * intensity);
    result_color.g = (uint8_t)(closest_object->material.color.g * intensity);
    result_color.b = (uint8_t)(closest_object->material.color.b * intensity);
    return (result_color);
}