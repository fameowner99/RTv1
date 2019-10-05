/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning_calculation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:13:37 by vmiachko          #+#    #+#             */
/*   Updated: 2019/10/05 17:13:39 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


float       get_intensity(t_vec normal, t_vec point)
{

}

t_vec      get_normal(t_object *object, t_vec point)
{

}

t_color	    get_color_with_light(t_union *un, t_object *closest_object, float closest_root, t_vec viewport)
{
    t_color result_color;
    float   intensity;
    t_vec   point;

    if (!closest_object)
        return g_background_color;

    point =  vec_add(un->camera.basis.position, vec_mul(vec_sub(viewport, un->camera.basis.position), closest_root));
  
    intensity = 1;//get_intensity(get_normal(closest_object, point), point);

    result_color.r = closest_object->color.r * intensity;
    result_color.g = closest_object->color.g * intensity;
    result_color.b = closest_object->color.b * intensity;
    return (result_color);
}