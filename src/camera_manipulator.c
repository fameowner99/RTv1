/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_manipulator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:47:11 by vmiachko          #+#    #+#             */
/*   Updated: 2019/09/07 16:47:22 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void move_camera(t_union *un, t_camera_move direction)
{
    t_vec *camera_position;
    t_vec look_at;

    camera_position = &un->camera.basis.position;
    look_at = un->camera.basis.look_at;

    if (direction == FORWARD)
    {
        vec_set(camera_position, camera_position->x + look_at.x * CAMERA_MOVEMENT_STEP,
           camera_position->y + look_at.y * CAMERA_MOVEMENT_STEP,
           camera_position->z + look_at.z * CAMERA_MOVEMENT_STEP);
         if (un->camera.basis.position.z >= 0)
            un->camera.projection_plane_distance = un->camera.basis.position.z + 1;
        else
            un->camera.projection_plane_distance = 1;
    }
    else if (direction == BACK)
    {
        look_at = vec_opposite(un->camera.basis.look_at);
        vec_set(camera_position, camera_position->x + look_at.x * CAMERA_MOVEMENT_STEP,
           camera_position->y + look_at.y * CAMERA_MOVEMENT_STEP,
           camera_position->z + look_at.z * CAMERA_MOVEMENT_STEP);
        if (un->camera.basis.position.z >= 0)
            un->camera.projection_plane_distance = un->camera.basis.position.z + 1;
        else
            un->camera.projection_plane_distance = 1;
    }
    else if (direction == LEFT)
    {
         vec_set(camera_position, camera_position->x - CAMERA_MOVEMENT_STEP,
           camera_position->y, camera_position->z); //temporary solution
    }
    else if (direction == RIGHT)
    {
        vec_set(camera_position, camera_position->x + CAMERA_MOVEMENT_STEP,
           camera_position->y, camera_position->z); //temporary solution
    }

    draw(un);
}