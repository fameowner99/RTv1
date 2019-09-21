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

    
    un->lst = object_push_back(un->lst, create_sphere_node(center, 1, SPHERE, color));

    color.r = 100;
    color.g = 100;
    color.b = 100;
    center.x = 0.5;
    center.y = 0;
    center.z = 5;
    un->lst = object_push_back(un->lst, create_sphere_node(center, 1, SPHERE, color));


    color.r = 0;
    color.g = 255;
    color.b = 0;
    center.x = 0.5;
    center.y = 0;
    center.z = 10;
    un->lst = object_push_back(un->lst, create_sphere_node(center, 1, SPHERE, color));



    color.r = 255;
    color.g = 4;
    color.b = 4;
    center.x = 0;
    center.y = 0;
    center.z = -7;

    
    un->lst = object_push_back(un->lst, create_sphere_node(center, 1, SPHERE, color));


//plane
    color.r = 10;
    color.g = 4;
    color.b = 255;
    center.x = 0;
    center.y = -3;
    center.z = 0;
    
    t_vec n;
    n.x = 0;
    n.y = -1;
    n.z = 0;

    un->lst = object_push_back(un->lst, create_plane_node(center, n, PLANE, color));


//cylinder 
    color.r = 255;
    color.g = 255;
    color.b = 255;
    t_cylinder c;
    vec_set(&c.axis, -1, 0, 0);
    vec_set(&c.cap, 0, 0, 5);
    c.max = 1;
    c.r = 1;

    un->lst = object_push_back(un->lst, create_cylinder_node(c, CYLINDER, color));

}