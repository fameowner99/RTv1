#ifndef PARSER_H

# define PARSER_H

#include "cJSON/cJSON.h"
#include "rtv1.h"

unsigned load_sphere(cJSON *objects, int object_index, t_union *un);
unsigned load_cone(cJSON *objects, int object_index, t_union *un);
unsigned load_cylinder(cJSON *objects, int object_index, t_union *un);
unsigned load_plane(cJSON *objects, int object_index, t_union *un);
unsigned load_point_light(cJSON *objects, int object_index, t_union *un);
unsigned load_polygon(cJSON *objects, int object_index, t_union *un);
unsigned validate_json_sphere(cJSON *object);
unsigned validate_json_cone(cJSON *object);
unsigned validate_json_cylinder(cJSON *object);
unsigned validate_json_plane(cJSON *object);
unsigned validate_scene_data(const cJSON *root);
unsigned validate_json_point_light(cJSON *object);
unsigned validate_json_polygon(cJSON *object);
int check_json_length(cJSON *object, int expected_length);
void load_scene_data(cJSON *root, t_union *un);
unsigned load_object_array(cJSON *objects, t_union *un, unsigned (*loader)(cJSON*, int, t_union*));
char				*read_file(const char *path, size_t *length);

#endif