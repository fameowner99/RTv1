#include "parser.h"



/*
 *
    t_sphere sphere;
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
 */

void load_spheres(cJSON *spheres, t_union *un)
{
	int spheres_count;
	t_sphere sphere_data;
	t_material material;
	int i = 0;
	cJSON *sphere;
	t_object *obj = NULL;

	spheres_count = cJSON_GetArraySize(spheres);
	while (i < spheres_count)
	{
		sphere = cJSON_GetArrayItem(spheres, i);
		sphere_data.radius = cJSON_GetObjectItem(sphere, "radius")->valuedouble;
		sphere_data.center.x = cJSON_GetObjectItem(sphere, "center_x")->valuedouble;
		sphere_data.center.y = cJSON_GetObjectItem(sphere, "center_y")->valuedouble;
		sphere_data.center.z = cJSON_GetObjectItem(sphere, "center_z")->valuedouble;
		material.color.r = cJSON_GetObjectItem(sphere, "color_r")->valueint;
		material.color.g = cJSON_GetObjectItem(sphere, "color_g")->valueint;
		material.color.b = cJSON_GetObjectItem(sphere, "color_b")->valueint;
		material.specular = cJSON_GetObjectItem(sphere, "specular")->valueint;
		obj = create_sphere_node(&sphere_data, SPHERE, material.color);
		obj->material.specular = material.specular;
		un->objects = object_push_back(un->objects, obj);
		++i;
	}
}
