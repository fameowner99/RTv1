/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:02 by vmiachko          #+#    #+#             */
/*   Updated: 2019/07/07 17:04:03 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"


static t_object       *create_node(void *data, t_object_type type, t_color color)
{
    t_object   *node;

    node = malloc(sizeof(t_object));
    node->type = type;
    node->color.r = color.r;
    node->color.g = color.g;
    node->color.b = color.b;
    node->data = data;
    node->next = NULL;
    return (node);
}


t_object        *create_sphere_node(t_sphere *a_data, t_object_type type, t_color color)
{
    t_sphere        *data;

    data = malloc(sizeof(t_sphere));
    data->radius = a_data->radius;
    vec_set_v(&data->center, a_data->center);
    return (create_node(data, type, color));
}

t_object        *create_plane_node(t_plane *a_data, t_object_type type, t_color color)
{
    t_plane *data;

    data = malloc(sizeof(t_plane));
    vec_set_v(&data->center, a_data->center);
    vec_set_v(&data->normal, vec_unit(a_data->normal));
    return (create_node(data, type, color));
}

t_object       *create_cylinder_node(t_cylinder *a_data, t_object_type type, t_color color)
{
    t_cylinder *data;

    data = malloc(sizeof(t_cylinder));
    vec_set_v(&data->axis, vec_unit(a_data->axis));
    vec_set_v(&data->cap, a_data->cap);
    data->max = a_data->max;
    data->r = a_data->r;

    return (create_node(data, type, color));
}

t_object        *create_cone_node(t_cone *a_data, t_object_type type, t_color color)
{
    t_cone      *data;

    data = malloc(sizeof(t_cone));
    vec_set_v(&data->vertex, a_data->vertex);
    vec_set_v(&data->axis, vec_unit(a_data->axis));
    data->tg = a_data->tg;
    data->min = a_data->min;
    data->max = a_data->max;
    return (create_node(data, type, color));
}

t_object      *object_push_back(t_object *head, t_object *node)
{
    t_object    *current_node;

    if (!head)
        return (node);
    current_node = head;

    while (current_node->next)
        current_node = current_node->next;
    current_node->next = node;
    return (head);
}
