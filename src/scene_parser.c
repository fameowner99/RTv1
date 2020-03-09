#include "parser.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int                 parse_arguments(int argc, char **argv, t_union *un)
{
	int i = 1;
	int result;

	result = FALSE;

	while (i < argc)
	{
		result |= parse_scene(argv[i], un);
		++i;
	}

    return (result);
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

char				*read_json_file(char *scene_path)
{
	int fd;
	char *line;
	char *json_str;

	json_str = NULL;
	fd = open(scene_path, O_RDONLY);

	while (get_next_line(fd, &line) > 0)
	{
		json_str = ft_append(json_str, line);
		free(line);
	}
	close(fd);
	return (json_str);
}


int                 parse_scene(char *scene_path, t_union *un)
{
	char *json_str;

	if (!check_extension(scene_path))
		return (FALSE);

	json_str = read_json_file(scene_path);

	if (!json_str)
		return FALSE;

	cJSON *root = cJSON_Parse(json_str);

	cJSON *spheres = cJSON_GetObjectItem(root, "spheres");
	//cJSON *cones = cJSON_GetObjectItem(root, "cones");
	//cJSON *cylinders = cJSON_GetObjectItem(root, "cylinders");
	//cJSON *planes = cJSON_GetObjectItem(root, "planes");
	//cJSON *meshes = cJSON_GetObjectItem(root, "meshes");
	//cJSON *point_lights = cJSON_GetObjectItem(root, "point_lights");

	load_spheres(spheres, un);


	cJSON_Delete(root);

	return (TRUE);
}
