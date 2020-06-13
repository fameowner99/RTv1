#include "parser.h"
#include "parser_defines.h"

int check_json_length(cJSON *object, const int expected_length)
{
    cJSON *it;
    int counter;

    it = object->child;
    counter = 0;
    while (it)
    {
        ++counter;
        it = it->next;
    }
    return (counter == expected_length);
}

unsigned is_material_set(cJSON *object)
{
    return (cJSON_GetObjectItem(object, COLOR_R) != NULL
    && cJSON_GetObjectItem(object, COLOR_G) != NULL
    && cJSON_GetObjectItem(object, COLOR_B) != NULL
    && cJSON_GetObjectItem(object, SPECULAR) != NULL);
}

unsigned validate_json_sphere(cJSON *object)
{
    return (cJSON_GetObjectItem(object, RADIUS) != NULL
            && cJSON_GetObjectItem(object, CENTER_X) != NULL
            && cJSON_GetObjectItem(object, CENTER_Y) != NULL
            && cJSON_GetObjectItem(object, CENTER_Z) != NULL
            && is_material_set(object));
}

unsigned validate_json_cone(cJSON *object)
{
    return (cJSON_GetObjectItem(object, VERTEX_X) != NULL
            && cJSON_GetObjectItem(object, VERTEX_Y) != NULL
            && cJSON_GetObjectItem(object, VERTEX_Z) != NULL
            && cJSON_GetObjectItem(object, AXIS_X) != NULL
            && cJSON_GetObjectItem(object, AXIS_Y) != NULL
            && cJSON_GetObjectItem(object, AXIS_Z) != NULL
            && cJSON_GetObjectItem(object, ANGLE) != NULL
            && cJSON_GetObjectItem(object, MIN) != NULL
            && cJSON_GetObjectItem(object, MAX) != NULL
            && is_material_set(object));
}

unsigned validate_json_cylinder(cJSON *object)
{
    return (cJSON_GetObjectItem(object, VERTEX_X) != NULL
            && cJSON_GetObjectItem(object, VERTEX_Y) != NULL
            && cJSON_GetObjectItem(object, VERTEX_Z) != NULL
            && cJSON_GetObjectItem(object, AXIS_X) != NULL
            && cJSON_GetObjectItem(object, AXIS_Y) != NULL
            && cJSON_GetObjectItem(object, AXIS_Z) != NULL
            && cJSON_GetObjectItem(object, RADIUS) != NULL
            && cJSON_GetObjectItem(object, MAX) != NULL
            && is_material_set(object));
}

unsigned validate_json_plane(cJSON *object)
{
    return (cJSON_GetObjectItem(object, CENTER_X) != NULL
            && cJSON_GetObjectItem(object, CENTER_Y) != NULL
            && cJSON_GetObjectItem(object, CENTER_Z) != NULL
            && cJSON_GetObjectItem(object, NORMAL_X) != NULL
            && cJSON_GetObjectItem(object, NORMAL_Y) != NULL
            && cJSON_GetObjectItem(object, NORMAL_Z) != NULL
            && is_material_set(object));
}

unsigned validate_json_point_light(cJSON *object)
{
    return (cJSON_GetObjectItem(object, CENTER_X) != NULL
            && cJSON_GetObjectItem(object, CENTER_Y) != NULL
            && cJSON_GetObjectItem(object, CENTER_Z) != NULL
            && cJSON_GetObjectItem(object, INTENSITY) != NULL);
}

unsigned validate_json_polygon(cJSON *object)
{
    return (cJSON_GetObjectItem(object, FILEPATH) != NULL);
}
