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


float       get_intensity(t_union *un, t_vec normal, t_vec point)
{
    t_light *light;
    t_vec    l;
    float   intensity;
    float   cos_alpha;

    intensity = 0;
    light = un->lights;
    while (light)
    {
        if (light->type == AMBIENT)
            intensity += light->intensity;
        else if (light->type == POINT)
        {
            l = vec_unit(vec_sub(light->position, point));
            cos_alpha = vec_dot_product(l, normal);
            if (cos_alpha > 0)
                intensity += cos_alpha * light->intensity;
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
    point =  vec_add(un->camera.basis.position, vec_mul(vec_unit(vec_sub(viewport, un->camera.basis.position)), closest_root));
    if (closest_object)
    intensity = get_intensity(un, get_normal(closest_object, point, viewport, closest_root, un), point);
    result_color.r = closest_object->color.r * intensity;
    result_color.g = closest_object->color.g * intensity;
    result_color.b = closest_object->color.b * intensity;
    return (result_color);
}