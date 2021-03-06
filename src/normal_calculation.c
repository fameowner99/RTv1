/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 14:14:25 by vmiachko          #+#    #+#             */
/*   Updated: 2019/10/06 14:14:27 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec get_normal_sphere(t_object *object, t_vec point)
{
    t_sphere *data;

    if (object->type != SPHERE)
    {
        ft_printf(RED"Error during calculation sphere normal\n"RESET);
        exit(666);
    }
    data = (t_sphere *)object->data;
    return (vec_unit(vec_sub(point, data->center)));
}


t_vec				get_normal_plane(t_object *object, t_vec point)
{
    t_plane *data;

    if (object->type != PLANE)
    {
       	ft_printf(RED"Error during calculation plane normal\n"RESET);
        exit(666);
    }
    data = (t_plane *)object->data;

    return (data->normal);
}

t_vec				get_normal_cylinder(t_object *object, t_vec point, t_vec viewport, float closest_root, t_union *un)
{
    t_cylinder *data;
    float       m;

    if (object->type != CYLINDER)
    {
       	ft_printf(RED"Error during calculation cylinder normal\n"RESET);
        exit(666);
    }
    data = (t_cylinder *)object->data;
    m =  closest_root * vec_dot_product(viewport, data->axis) +
            vec_dot_product(vec_sub(un->camera.basis.position, data->cap), data->axis);
    return (vec_unit(vec_sub(vec_sub(point, data->cap), vec_mul(data->axis, m))));
}

t_vec				get_normal_cone(t_object *object, t_vec point, t_vec viewport, float closest_root, t_union *un)
{
    t_cone *data;
    float       m;

    if (object->type != CONE)
    {
        ft_printf(RED"Error during calculation cone normal\n"RESET);
        exit(666);
    }
    data = (t_cone *)object->data;
    m =  closest_root * vec_dot_product(viewport, data->axis) +
         vec_dot_product(vec_sub(un->camera.basis.position, data->axis), data->axis);

    return (vec_unit(vec_sub(vec_sub(point, data->vertex), vec_mul(data->axis, m * (1 + data->tg * data->tg)))));
}