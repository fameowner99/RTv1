/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:40:55 by vmiachko          #+#    #+#             */
/*   Updated: 2019/07/07 17:02:24 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# define W_WIDTH 	800
# define W_HEIGHT	800
# define TRUE		1
# define FALSE		0


typedef enum			e_object_type
{
	PLANE = 0
	SPHERE,
	CYLINDER,
	CONE
}						t_object_type;

typedef struct			s_point
{
	float				x;
	float				y;
	float				z;
}						t_point;

typedef struct			s_sphere
{
	int					radius;
}						t_sphere;

typedef struct			s_object
{
	t_point				center;
	void				*object_data;
	t_object_type		type;
}						t_object;


typedef struct			s_object_lst
{
	t_object			*object;
	struct s_object_lst	*next;
}						t_object_lst;

#endif
