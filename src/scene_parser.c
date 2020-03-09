#include "rtv1.h"
#include  "json.h"

int                 parse_scene(int argc, char **argv, t_union *un)
{

    struct json_object *parsed_json;
    struct json_object *objects;
    struct json_object *object;
    size_t n_objects;
    int i = 0;


    char *str = "{\"object\":[{ \"type\":\"SPHERE\"}, {\"type\": \"CONE\"}]}";

    parsed_json = json_tokener_parse(str);

    printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));\
    printf(RED"_______________________________________\n"RESET);
    json_object_object_get_ex(parsed_json, "object", &objects);

    n_objects = json_object_array_length(objects);

   /* for(i=0;i<n_friends;i++) {
        friend = json_object_array_get_idx(friends, i);
        printf("%lu. %s\n",i+1,json_object_get_string(friend));
    }*/

   while (i < n_objects)
   {
        object = json_object_array_get_idx(objects, i);
       printf("%u. %s\n",i+1,json_object_get_string(object));

       ++i;
   }


    return FALSE;
}