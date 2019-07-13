/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:40:51 by vmiachko          #+#    #+#             */
/*   Updated: 2019/07/13 14:41:40 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_ininial_camera_position(t_union *un)
{
	un->camera.position.x = 0;
	un->camera.position.y = 0;
	un->camera.position.z = 0;
}

int		main()
{
	t_union un;

	un.lst = NULL;
	set_initial_camera_position(&un);
	add_objects_to_scene(&un);
	rt(&un);
	return (0);
}
