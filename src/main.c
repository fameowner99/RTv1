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

void	set_initial_camera_data(t_union *un)
{
	vec_set(&un->camera.basis.position, 0, 0, 0);
	vec_set(&un->camera.basis.up, 0, 1, 0);
	vec_set(&un->camera.basis.look_at, 0, 0 , 1);
	un->camera.projection_plane_distance = un->camera.basis.position.z + 1;
}

int		main()
{
	t_union un;

	un.lst = NULL;
	set_initial_camera_data(&un);
	add_objects_to_scene(&un);
	rt(&un);
	return (0);
}
