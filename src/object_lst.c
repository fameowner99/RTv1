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


t_object        *create_sphere_node(t_vec center, float radius, t_object_type type, t_color color)
{
    t_sphere        *data;

    data = malloc(sizeof(t_sphere));
    data->radius = radius;
    vec_set(&data->center, center.x, center.y, center.z);
    return (create_node(data, type, color));
}

t_object        *create_plane_node(t_vec center, t_vec normal, t_object_type type, t_color color)
{
    t_plane *data;

    data = malloc(sizeof(t_plane));
    vec_set(&data->center, center.x, center.y, center.z);
    vec_set(&data->normal, normal.x, normal.y, normal.z);
    return (create_node(data, type, color));
}

t_object       *create_cylinder_node(t_cylinder a_data, t_object_type type, t_color color)
{
    t_cylinder *data;

    data = malloc(sizeof(t_cylinder));
    vec_set(&data->axis, a_data.axis.x, a_data.axis.y, a_data.axis.z);
    vec_set(&data->cap, a_data.cap.x, a_data.cap.y, a_data.cap.z);
    data->max = a_data.max;
    data->r = a_data.r;

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
