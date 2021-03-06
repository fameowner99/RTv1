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
    }
    else if (direction == BACK)
    {
        look_at = vec_opposite(un->camera.basis.look_at);
        vec_set(camera_position, camera_position->x + look_at.x * CAMERA_MOVEMENT_STEP,
           camera_position->y + look_at.y * CAMERA_MOVEMENT_STEP,
           camera_position->z + look_at.z * CAMERA_MOVEMENT_STEP);
    }
    else if (direction == LEFT)
    {
        t_vec vec_cross = vec_cross_product(un->camera.basis.look_at, un->camera.basis.up);
         vec_set(camera_position, camera_position->x + vec_cross.x * CAMERA_MOVEMENT_STEP,
           camera_position->y + vec_cross.y * CAMERA_MOVEMENT_STEP,
           camera_position->z + vec_cross.z * CAMERA_MOVEMENT_STEP);
    }
    else if (direction == RIGHT)
    {
        t_vec vec_cross = vec_cross_product(un->camera.basis.up, un->camera.basis.look_at);
        vec_set(camera_position, camera_position->x + vec_cross.x * CAMERA_MOVEMENT_STEP,
                camera_position->y + vec_cross.y * CAMERA_MOVEMENT_STEP,
                camera_position->z + vec_cross.z * CAMERA_MOVEMENT_STEP);
    }

    draw(un);
}


void                update_camera_vectors(t_union *un)
{
    un->camera.basis.look_at = apply_rotate_matrix(un->camera.basis.look_at, &un->camera.matrix);
    un->camera.basis.up = apply_rotate_matrix(un->camera.basis.up, &un->camera.matrix);
}