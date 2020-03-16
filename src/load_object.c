#include "parser.h"
#include "parser_defines.h"

unsigned load_object_array(cJSON *objects, t_union *un, unsigned (*loader)(cJSON*, int, t_union*))
{
	int objects_count;

	int i = 0;

	objects_count = cJSON_GetArraySize(objects);
	while (i < objects_count)
	{
        if (!loader(objects, i, un))
            return (FALSE);
		++i;
	}
	return (TRUE);
}

unsigned load_sphere(cJSON *objects, int object_index, t_union *un)
{
    cJSON *sphere;
    t_sphere sphere_data;
    t_material material;
    t_object *obj = NULL;

    sphere = cJSON_GetArrayItem(objects, object_index);
    if (!validate_json_sphere(sphere))
        return (FALSE);
    sphere_data.radius = (float)cJSON_GetObjectItem(sphere, RADIUS)->valuedouble;
    vec_set(&sphere_data.center,
            (float)cJSON_GetObjectItem(sphere, CENTER_X)->valuedouble,
            (float)cJSON_GetObjectItem(sphere, CENTER_Y)->valuedouble,
            (float)cJSON_GetObjectItem(sphere, CENTER_Z)->valuedouble);
    material.color.r = cJSON_GetObjectItem(sphere, COLOR_R)->valueint;
    material.color.g = cJSON_GetObjectItem(sphere, COLOR_G)->valueint;
    material.color.b = cJSON_GetObjectItem(sphere, COLOR_B)->valueint;
    material.specular = cJSON_GetObjectItem(sphere, SPECULAR)->valueint;
    obj = create_sphere_node(&sphere_data, SPHERE, material.color);
    obj->material.specular = material.specular;
    un->objects = object_push_back(un->objects, obj);
    return (TRUE);
}

unsigned load_cone(cJSON *objects, int object_index, t_union *un)
{
    cJSON *cone;
    t_cone cone_data;
    t_material material;
    t_object *obj = NULL;

    cone = cJSON_GetArrayItem(objects, object_index);
    if (!validate_json_cone(cone))
        return (FALSE);
    vec_set(&cone_data.vertex,
            (float)cJSON_GetObjectItem(cone, VERTEX_X)->valuedouble,
            (float)cJSON_GetObjectItem(cone, VERTEX_Y)->valuedouble,
            (float)cJSON_GetObjectItem(cone, VERTEX_Z)->valuedouble);
    vec_set(&cone_data.axis,
            (float)cJSON_GetObjectItem(cone, AXIS_X)->valuedouble,
            (float)cJSON_GetObjectItem(cone, AXIS_Y)->valuedouble,
            (float)cJSON_GetObjectItem(cone, AXIS_Z)->valuedouble);
    cone_data.tg = (float)tan(cJSON_GetObjectItem(cone, ANGLE)->valuedouble * M_PI / 180.);
    cone_data.min = (float)cJSON_GetObjectItem(cone, MIN)->valuedouble;
    cone_data.max = (float)cJSON_GetObjectItem(cone, MAX)->valuedouble;
    material.color.r = cJSON_GetObjectItem(cone, COLOR_R)->valueint;
    material.color.g = cJSON_GetObjectItem(cone, COLOR_G)->valueint;
    material.color.b = cJSON_GetObjectItem(cone, COLOR_B)->valueint;
    material.specular = cJSON_GetObjectItem(cone, SPECULAR)->valueint;
    obj = create_cone_node(&cone_data, CONE, material.color);
    obj->material.specular = material.specular;
    un->objects = object_push_back(un->objects, obj);
    return (TRUE);
}


unsigned load_cylinder(cJSON *objects, int object_index, t_union *un)
{
    cJSON *cylinder;
    t_cylinder cylinder_data;
    t_material material;
    t_object *obj = NULL;

    cylinder = cJSON_GetArrayItem(objects, object_index);
    if (!validate_json_cylinder(cylinder))
        return (FALSE);

    vec_set(&cylinder_data.cap,
            (float)cJSON_GetObjectItem(cylinder, VERTEX_X)->valuedouble,
            (float)cJSON_GetObjectItem(cylinder, VERTEX_Y)->valuedouble,
            (float)cJSON_GetObjectItem(cylinder, VERTEX_Z)->valuedouble);
    vec_set(&cylinder_data.axis,
            (float)cJSON_GetObjectItem(cylinder, AXIS_X)->valuedouble,
            (float)cJSON_GetObjectItem(cylinder, AXIS_Y)->valuedouble,
            (float)cJSON_GetObjectItem(cylinder, AXIS_Z)->valuedouble);
    cylinder_data.radius =  (float)cJSON_GetObjectItem(cylinder, RADIUS)->valuedouble;
    cylinder_data.max = (float)cJSON_GetObjectItem(cylinder, MAX)->valuedouble;
    material.color.r = cJSON_GetObjectItem(cylinder, COLOR_R)->valueint;
    material.color.g = cJSON_GetObjectItem(cylinder, COLOR_G)->valueint;
    material.color.b = cJSON_GetObjectItem(cylinder, COLOR_B)->valueint;
    material.specular = cJSON_GetObjectItem(cylinder, SPECULAR)->valueint;
    obj = create_cylinder_node(&cylinder_data, CYLINDER, material.color);
    obj->material.specular = material.specular;
    un->objects = object_push_back(un->objects, obj);
    return (TRUE);
}

unsigned load_plane(cJSON *objects, int object_index, t_union *un)
{
    cJSON *plane;
    t_plane plane_data;
    t_material material;
    t_object *obj = NULL;

    plane = cJSON_GetArrayItem(objects, object_index);
    if (!validate_json_plane(plane))
        return (FALSE);
    vec_set(&plane_data.center,
            (float)cJSON_GetObjectItem(plane, CENTER_X)->valuedouble,
            (float)cJSON_GetObjectItem(plane, CENTER_Y)->valuedouble,
            (float)cJSON_GetObjectItem(plane, CENTER_Z)->valuedouble);
    vec_set(&plane_data.normal,
            (float)cJSON_GetObjectItem(plane, NORMAL_X)->valuedouble,
            (float)cJSON_GetObjectItem(plane, NORMAL_Y)->valuedouble,
            (float)cJSON_GetObjectItem(plane, NORMAL_Z)->valuedouble);
    material.color.r = cJSON_GetObjectItem(plane, COLOR_R)->valueint;
    material.color.g = cJSON_GetObjectItem(plane, COLOR_G)->valueint;
    material.color.b = cJSON_GetObjectItem(plane, COLOR_B)->valueint;
    material.specular = cJSON_GetObjectItem(plane, SPECULAR)->valueint;
    obj = create_plane_node(&plane_data, PLANE, material.color);
    obj->material.specular = material.specular;
    un->objects = object_push_back(un->objects, obj);
    return (TRUE);
}

unsigned load_point_light(cJSON *objects, int object_index, t_union *un)
{
    t_light light_data;
    cJSON *light;

    light = cJSON_GetArrayItem(objects, object_index);
    if (!validate_json_point_light(light))
        return (FALSE);

    light_data.type = POINT;
    vec_set(&light_data.position,
            (float)cJSON_GetObjectItem(light, CENTER_X)->valuedouble,
            (float)cJSON_GetObjectItem(light, CENTER_Y)->valuedouble,
            (float)cJSON_GetObjectItem(light, CENTER_Z)->valuedouble);
    light_data.intensity = (float)cJSON_GetObjectItem(light, INTENSITY)->valuedouble;
    un->lights = light_push_back(un->lights, &light_data);
}