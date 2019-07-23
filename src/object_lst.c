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


t_object_lst        *create_node(void *data, t_object_type type, t_color color)
{
    t_object_lst    *node;

    node = malloc(sizeof(t_object_lst));
    node->type = type;
    node->color.r = color.r;
    node->color.g = color.g;
    node->color.b = color.b;
    node->data = data;
    node->next = NULL;
    return (node);
}


t_object_lst        *create_sphere_node(t_vec center, int radius, t_object_type type, t_color color)
{
    t_sphere        *data;

    data = malloc(sizeof(t_sphere));
    data->radius = radius;
    data->center.x = center.x;
    data->center.y = center.y;
    data->center.z = center.z;
    return (create_node(data, type, color));
}


t_object_lst        *push_back(t_object_lst *head, t_object_lst *node)
{
    if (!head)
        return (node);
    
    while (head->next)
    {
        head = head->next;
    }
    head->next = node;
    return (head);
}
