#include "rtv1.h"

void				add_objects_to_scene(t_union *un)
{
    t_vec        center;
    t_color      color;

    color.r = 255;
    color.g = 4;
    color.b = 4;
    center.x = -0.5;
    center.y = 0;
    center.z = 5;

    
    un->lst = push_back(un->lst, create_sphere_node(center, 1, SPHERE, color));

    color.r = 100;
    color.g = 100;
    color.b = 100;
    center.x = 0.5;
    center.y = 0;
    center.z = 5;
    un->lst = push_back(un->lst, create_sphere_node(center, 1, SPHERE, color));
}