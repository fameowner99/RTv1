#include "rtv1.h"

void				add_objects_to_scene(t_union *un)
{

/*    t_sphere sphere;
    t_plane  plane;
    t_cylinder cylinder;
    t_cone      cone;
    t_color      color;
    t_light     light;
    t_object *obj = NULL;

    color.r = 255;
    color.g = 4;
    color.b = 4;
    vec_set(&sphere.center, -0.5, 0, 5);
    sphere.radius = 1;

    obj = create_sphere_node(&sphere, SPHERE, color);
    obj->specular = 100;
    un->objects = object_push_back(un->objects, obj);

    color.r = 100;
    color.g = 100;
    color.b = 100;
    vec_set(&sphere.center, 0.5, 0, 5);
    sphere.radius = 1;
    obj = create_sphere_node(&sphere, SPHERE, color);
    obj->specular = 200;
    un->objects = object_push_back(un->objects, obj);

    color.r = 0;
    color.g = 255;
    color.b = 0;

    vec_set(&sphere.center, 0.5, 0, 10);
    sphere.radius = 1;
    obj = create_sphere_node(&sphere, SPHERE, color);
    obj->specular = 10;
    un->objects = object_push_back(un->objects, obj);

    color.r = 255;
    color.g = 4;
    color.b = 4;
    vec_set(&sphere.center, 0, 0, -7);
    sphere.radius = 1;
	obj = create_sphere_node(&sphere, SPHERE, color);
	obj->specular = 2000;
    un->objects = object_push_back(un->objects, obj);


//plane
    color.r = 10;
    color.g = 4;
    color.b = 255;

    vec_set(&plane.center, 0, -1, 0);
    vec_set(&plane.normal, 0, 1, 0);
    obj = create_plane_node(&plane, PLANE, color);
    obj->specular = 45;
    un->objects = object_push_back(un->objects, obj);


//plane
    color.r = 10;
    color.g = 255;
    color.b = 255;

    vec_set(&plane.center, 0, 0, 100);
    vec_set(&plane.normal, 0, 0, -1);
	obj = create_plane_node(&plane, PLANE, color);
	obj->specular = 500;
    un->objects = object_push_back(un->objects, obj);

//cylinder
    color.r = 255;
    color.g = 255;
    color.b = 255;

    vec_set(&cylinder.axis, 0, 1, 0);
    vec_set(&cylinder.cap, 0, 0, 6);
    cylinder.max = 1;
    cylinder.r = 1;


	obj = create_cylinder_node(&cylinder, CYLINDER, color);
	obj->specular = 1;
    un->objects = object_push_back(un->objects, obj);


//cone

    color.r = 255;
    color.g = 255;
    color.b = 0;
    vec_set(&cone.vertex, -4, 5, 10);
    vec_set(&cone.axis, 0, -1, 0);
    cone.tg = tan(45 * M_PI / 180);
    cone.min = 0;
    cone.max = 5;

    obj = create_cone_node(&cone, CONE, color);
    obj->specular = 150;
    un->objects = object_push_back(un->objects, obj);



    //light
    light.intensity = 0.3;
    light.type = AMBIENT;
    //un->lights = light_push_back(un->lights, &light);


    light.intensity = 0.3;
    light.type = POINT;
    vec_set(&light.position, 0, 0, -5);
    un->lights = light_push_back(un->lights, &light);

    light.intensity = 0.5;
    light.type = POINT;
    vec_set(&light.position, 10, 0, 5);
    un->lights = light_push_back(un->lights, &light);*/
}
