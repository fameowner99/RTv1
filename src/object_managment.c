#include "rtv1.h"

void				add_objects_to_scene(t_union *un)
{

    t_sphere sphere;
    t_plane  plane;
    t_cylinder cylinder;
    t_cone      cone;
    t_color      color;
    t_light     light;

    color.r = 255;
    color.g = 4;
    color.b = 4;
    vec_set(&sphere.center, -0.5, 0, 5);
    sphere.radius = 1;
 
    un->objects = object_push_back(un->objects, create_sphere_node(&sphere, SPHERE, color));

    color.r = 100;
    color.g = 100;
    color.b = 100;
    vec_set(&sphere.center, 0.5, 0, 5);
    sphere.radius = 1;
    un->objects = object_push_back(un->objects, create_sphere_node(&sphere, SPHERE, color));

    color.r = 0;
    color.g = 255;
    color.b = 0;

    vec_set(&sphere.center, 0.5, 0, 10);
    sphere.radius = 1;
    un->objects = object_push_back(un->objects, create_sphere_node(&sphere, SPHERE, color));

    color.r = 255;
    color.g = 4;
    color.b = 4;
    vec_set(&sphere.center, 0, 0, -7);
    sphere.radius = 1;

    un->objects = object_push_back(un->objects, create_sphere_node(&sphere, SPHERE, color));


//plane
    color.r = 10;
    color.g = 4;
    color.b = 255;

    vec_set(&plane.center, 0, -1, 0);
    vec_set(&plane.normal, 0, 1, 0);
    un->objects = object_push_back(un->objects, create_plane_node(&plane, PLANE, color));


//plane
    color.r = 10;
    color.g = 255;
    color.b = 255;

    vec_set(&plane.center, 0, 0, 100);
    vec_set(&plane.normal, 0, 0, -1);
    un->objects = object_push_back(un->objects, create_plane_node(&plane, PLANE, color));

//cylinder
    color.r = 255;
    color.g = 255;
    color.b = 255;

    vec_set(&cylinder.axis, 0, 1, 0);
    vec_set(&cylinder.cap, 0, 0, 6);
    cylinder.max = 1;
    cylinder.r = 1;

    un->objects = object_push_back(un->objects, create_cylinder_node(&cylinder, CYLINDER, color));


//cone

    color.r = 255;
    color.g = 255;
    color.b = 0;
    vec_set(&cone.vertex, -4, 5, 10);
    vec_set(&cone.axis, 0, -1, 0);
    cone.tg = tan(45 * M_PI / 180);
    cone.min = 0;
    cone.max = 5;

    un->objects = object_push_back(un->objects, create_cone_node(&cone, CONE, color));



    //light
    light.intensity = 0.3;
    light.type = AMBIENT;
    //un->lights = light_push_back(un->lights, &light);


    light.intensity = 0.5;
    light.type = POINT;
    vec_set(&light.position, 0, -10, -10);
    un->lights = light_push_back(un->lights, &light);

    light.intensity = 0.5;
    light.type = POINT;
    vec_set(&light.position, 0, 10, 10);
    un->lights = light_push_back(un->lights, &light);
}
