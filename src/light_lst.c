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

static t_light     *create_node(t_light *a_light)
{
    t_light *node;

    if (!(node = malloc(sizeof(t_light))))
        return NULL;
    vec_set_v(&node->position, a_light->position);
    node->type = a_light->type;
    node->intensity = a_light->intensity;
    node->next = NULL;
    return (node);
}

t_light     *light_push_back(t_light *head, t_light *a_light)
{
    t_light *current_node;

    if (!head)
        return (create_node(a_light));
    current_node = head;
    while (current_node->next)
        current_node = current_node->next;
    current_node->next = create_node(a_light);
    return (head);
}