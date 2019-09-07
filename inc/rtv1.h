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
# define VIEWPORT_X 1
# define VIEWPORT_Y 1

# define TRUE		1
# define FALSE		0
# define FPS 60
# define BACKGROUND_COLOR_R 0
# define BACKGROUND_COLOR_G 0
# define BACKGROUND_COLOR_B 0
# define CAMERA_MOVEMENT_STEP 1

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "libvec.h"

typedef enum			e_camera_move
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
	FORWARD,
	BACK
}						t_camera_move;

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

typedef struct			s_camera_basis
{
	t_vec				position;
	t_vec				look_at;
	t_vec				up;
}						t_camera_basis;

typedef struct			s_camera
{
	t_camera_basis		basis;
	float				projection_plane_distance;
}						t_camera;

typedef struct			s_union
{
	t_object_lst		*lst;
	t_sdl_data			sdl;
	t_camera			camera;
}						t_union;

typedef struct			s_equation_solve
{
	float				t1;
	float				t2;
}						t_equation_solve;

void				add_objects_to_scene(t_union *un);
t_object_lst        *create_sphere_node(t_vec center, int radius, t_object_type type, t_color color);
t_object_lst        *push_back(t_object_lst *head, t_object_lst *node);
void				rt(t_union *rt);
void				ray_intersection(t_union *un);
void				draw(t_union *un);
void				draw_on_canvas(t_union *un, t_object_lst *object, t_vec canvas);
t_equation_solve	solve_equation(t_union *un, float k1, float k2, float k3);
int					handle_events(t_union *un);
void				move_camera(t_union *un, t_camera_move direction);

#endif
