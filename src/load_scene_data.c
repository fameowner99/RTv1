#include "parser.h"
#include "parser_defines.h"



void load_scene_data(cJSON *root, t_union *un)
{
    t_light light;

    if (!validate_scene_data(root))
        return;

    light.type = AMBIENT;
    light.intensity = (float)cJSON_GetObjectItem(root, AMBIENT_LIGHT)->valuedouble;
    un->lights = light_push_back(un->lights, &light);
}