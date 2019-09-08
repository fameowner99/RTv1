/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:20:40 by vmiachko          #+#    #+#             */
/*   Updated: 2019/09/08 17:20:53 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_light     *create_node(t_light_type type, t_vec position, float intensity)
{
    t_light *node;

    node = malloc(sizeof(t_light));
    vec_set(&node->position, position.x, position.y, position.z);
    node->type = type;
    node->intensity = intensity;
    return (node);
}

t_light     *light_push_back(t_light *head, t_light_type type, t_vec position, float intensity)
{
    t_light *current_node;

    if (!head)
        return (create_node(type, position, intensity));
    current_node = head;
    while (current_node->next)
        current_node = current_node->next;
    current_node->next = create_node(type, position, intensity);
    return (head);
}