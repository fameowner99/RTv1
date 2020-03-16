#include "parser.h"
#include "parser_defines.h"

unsigned validate_scene_data(const cJSON *root)
{
    return (cJSON_GetObjectItem(root, AMBIENT_LIGHT) != NULL);
}