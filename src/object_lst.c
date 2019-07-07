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


#include "../inc.rtv1.h" //change

t_object_lst        *create_node(t_object *data)
{
    t_object_lst    *node;

    node = malloc(sizeof(t_object_lst));
    node->data = data;
    node->next = NULL;
    return (node);
}