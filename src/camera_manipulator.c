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

void update_projection_plane(t_union *un)
{
    if (un->camera.basis.position.z >= 0)
            un->camera.projection_plane_distance = un->camera.basis.position.z + 1;
    else
        un->camera.projection_plane_distance = 1;
}

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
        update_projection_plane(un);
    }
    else if (direction == BACK)
    {
        look_at = vec_opposite(un->camera.basis.look_at);
        vec_set(camera_position, camera_position->x + look_at.x * CAMERA_MOVEMENT_STEP,
           camera_position->y + look_at.y * CAMERA_MOVEMENT_STEP,
           camera_position->z + look_at.z * CAMERA_MOVEMENT_STEP);
        update_projection_plane(un);
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

void update_look_at(t_union *un)
{

}

void rotate_camera(t_union *un, t_camera_rotate direction)
{
    const float angle = 50;

    if (direction == Y_FORWARD)
    {
        /*float tmp = un->camera.basis.position.x;
        un->camera.basis.position.x = un->camera.basis.position.x * cos(angle) + un->camera.basis.position.z * sin(angle);
        un->camera.basis.position.z = - tmp * sin(angle) + un->camera.basis.position.z * cos(angle);*/
        //float tmp = un->camera.basis.position.x;
       // un->camera.basis.position.x = un->camera.basis.position.y * cos(angle) - un->camera.basis.position.z * sin(angle);
       // un->camera.basis.position.y = un->camera.basis.position.y * sin(angle) + un->camera.basis.position.z * cos(angle);
    }
    else if (direction == Y_BACK)
    {

    }
    else if (direction == X_LEFT)
    {

    }
    else if (direction == X_RIGHT)
    {
        
    }

   
    update_look_at(un);

   //draw(un);
}