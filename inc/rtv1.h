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

# define W_WIDTH 	1000
# define W_HEIGHT	1000
# define TRUE		1
# define FALSE		0
# define FPS 60

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "libft.h"
#include "libvec.h"

typedef enum			e_object_type
{
	PLANE = 0,
	SPHERE,
	CYLINDER,
	CONE
}						t_object_type;

typedef struct			s_sphere
{
	t_vec				center;
	int					radius;
}						t_sphere;

typedef struct			s_color
{
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
}						t_color;

typedef struct			s_object_lst
{
	void				*data;
	t_object_type		type;
	t_color				color;
	struct s_object_lst	*next;
}						t_object_lst;

typedef struct			s_sdl_data
{
	SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Event    event;
}						t_sdl_data;

typedef struct			s_camera
{
	t_vec				position;
}						t_camera;

typedef struct			s_union
{
	t_object_lst		*lst;
	t_sdl_data			sdl;
	t_camera			camera;
}						t_union;


void				add_objects_to_scene(t_union *un);
t_object_lst        *create_sphere_node(t_vec center, int radius, t_object_type type, t_color color);
t_object_lst        *push_back(t_object_lst *head, t_object_lst *node);
void				rt(t_union *rt);
void				ray_intersection(t_union *un);
void				draw(t_union *un);

#endif
