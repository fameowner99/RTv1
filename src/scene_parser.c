#include "parser.h"
#include "parser_defines.h"

unsigned                parse_arguments(int argc, char **argv, t_union *un)
{
	int i = 1;

	while (i < argc)
	{
		if (!parse_scene(argv[i], un))
		    return (FALSE);
		++i;
	}

    return (TRUE);
}

int					check_extension(char *scene_path)
{
	int length;
	int i;

	length = ft_strlen(scene_path);
	i = length - 1;
	while (i >= 0)
	{
		if (scene_path[i] == '.')
			break;
		--i;
	}
	if (i < 0)
		return (FALSE);

	return (!ft_strcmp(scene_path + i, ".rt"));
}

unsigned                parse_scene(char *scene_path, t_union *un)
{
	char *json_str;
	unsigned result;
    cJSON *object;
    size_t length;

	if (!check_extension(scene_path))
		return (FALSE);

	json_str = read_file(scene_path, &length);

	if (!json_str)
		return FALSE;

	cJSON *root = cJSON_Parse(json_str);
	if (!root)
	    return (FALSE);
    result = TRUE;

	load_scene_data(root, un);
	object = cJSON_GetObjectItem(root, SPHERES_ARR);
    result &= load_object_array(object, un, load_sphere);
	object = cJSON_GetObjectItem(root, CONES_ARR);
    result &= load_object_array(object, un, load_cone);
    object = cJSON_GetObjectItem(root, CYLINDERS_ARR);
    result &= load_object_array(object, un, load_cylinder);
	object = cJSON_GetObjectItem(root, PLANES_ARR);
	result &= load_object_array(object, un, load_plane);
	object = cJSON_GetObjectItem(root, POINT_LIGHTS_ARR);
    result &= load_object_array(object, un, load_point_light);
    object = cJSON_GetObjectItem(root, POLYGONS);
    result &= load_object_array(object, un, load_polygon);
    free(json_str);
	cJSON_Delete(root);
	return (result);
}
