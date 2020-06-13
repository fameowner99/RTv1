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

# define PROJECTION_PLANE_DISTANCE 1

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "libvec.h"
#include "libmatrix.h"
#include "float.h"
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
//#include <CL/cl.h>
#endif
# define INF FLT_MAX

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
	CONE,
	POLYGON
}						t_object_type;

typedef enum			e_light_type
{
	AMBIENT = 0,
	POINT
}						t_light_type;

typedef struct 			s_light
{
	t_light_type		type;
	t_vec				position;
	float				intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_plane
{
	t_vec				center;
	t_vec				normal;
}						t_plane;

typedef struct			s_sphere
{
	t_vec				center;
	float				radius;
}						t_sphere;

typedef struct 			s_cylinder
{
	float				radius;
	t_vec				cap;
	t_vec 				axis;
	float				max;		
}						t_cylinder;

typedef struct			s_cone
{
	t_vec				vertex;
	t_vec				axis;
	float				tg;
	float				min;
	float				max;
}						t_cone;

typedef struct			s_color
{
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
}						t_color;

typedef struct			s_material
{
	t_color				color;
	int					specular;
}						t_material;

typedef  struct         s_polygon
{
    float *vertices;
    int vertices_size;
    t_vec               min; //aabb
    t_vec               max; //aabb
	t_vec				intersected_triangle_normal;
}                       t_polygon;

typedef struct			s_object
{
	void				*data;
	t_object_type		type;
	t_material			material;
	struct s_object		*next;
}						t_object;

typedef struct			s_sdl_data
{
	SDL_Window   		*window;
    SDL_Renderer 		*renderer;
    SDL_Event    		event;
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
	t_matrix            matrix;
}						t_camera;

typedef struct          s_mouse
{
    int                 is_clicked;
    int                 clicked_x;
    int                 clicked_y;
}                       t_mouse;

typedef struct			s_union
{
	t_object			*objects;
	t_light				*lights;
	t_sdl_data			sdl;
	t_camera			camera;
	t_mouse             mouse;
}						t_union;

typedef struct			s_equation_solve
{
	float				t1;
	float				t2;
}						t_equation_solve;

t_color					g_background_color;

t_object      	 	*create_sphere_node(t_sphere *a_data, t_object_type type, t_color color);
t_object       		*create_plane_node(t_plane *a_data, t_object_type type, t_color color);
t_object       		*create_cylinder_node(t_cylinder *a_data, t_object_type type, t_color color);
t_object        	*create_cone_node(t_cone *a_data, t_object_type type, t_color color);
t_object            *create_polygon_node(t_polygon *a_data, t_object_type type, t_color color);
t_object	        *object_push_back(t_object *head, t_object *node);
t_light				*light_push_back(t_light *head, t_light *a_light);
void				rt(t_union *rt);
void				ray_intersection(t_union *un);
void				draw(t_union *un);
void				draw_on_canvas(t_union *un, t_color color, t_vec canvas);
t_equation_solve	solve_equation(float k1, float k2, float k3);
int					handle_events(t_union *un);
void				move_camera(t_union *un, t_camera_move direction);
void 				rotate_camera(t_union *un);
t_matrix            get_rotate_matrix(float angle_x, float angle_y);
t_color				get_color_with_light(t_union *un, t_object *closest_object, float closest_root, t_vec viewport);
t_vec				get_normal_sphere(t_object *object, t_vec point);
t_vec				get_normal_plane(t_object *object, t_vec point);
t_vec				get_normal_cylinder(t_object *object, t_vec point, t_vec viewport, float closest_root, t_union *un);
t_vec				get_normal_cone(t_object *object, t_vec point, t_vec viewport, float closest_root, t_union *un);
t_equation_solve 	sphere_ray_intersection(t_object *object, t_vec direction, t_vec start_point);
t_equation_solve 	plane_ray_intersection(t_object *object, t_vec direction, t_vec start_point);
t_equation_solve 	cylinder_ray_intersection(t_object *object, t_vec direction, t_vec start_point);
t_equation_solve	cone_ray_intersection(t_object *object, t_vec direction, t_vec start_point);
t_equation_solve 	polygon_ray_intersection(t_object *object, t_vec direction, t_vec start_point);
t_equation_solve 	triangle_ray_intersection(t_vec v0, t_vec v1, t_vec v2, t_vec direction, t_vec start_point);
unsigned            parse_arguments(int argc, char **argv, t_union *un);
unsigned            parse_scene(char *scene_path, t_union *un);
t_vec               apply_rotate_matrix(t_vec vec, t_matrix *matrix);
void                rotate_camera(t_union *un);
void                update_camera_vectors(t_union *un);

#endif
