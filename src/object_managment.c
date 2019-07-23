#include "rtv1.h"

void				add_objects_to_scene(t_union *un)
{
    t_vec        center;
    t_color      color;

    color.r = 255;
    color.g = 4;
    color.b = 4;
    center.x = 0;
    center.y = 0;
    center.z = 10;
    un->lst = push_back(un->lst, create_sphere_node(center, 2, SPHERE, color));
}