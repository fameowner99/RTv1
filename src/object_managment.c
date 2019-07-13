#include "rtv1.h"

void				add_objects_to_scene(t_union *un)
{
    t_vector        center;
    center.x = 3;
    center.y = 3;
    center.z = 3;
    un->lst = push_back(un->lst, create_sphere_node(center, 5, SPHERE));
}