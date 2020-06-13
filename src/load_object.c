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
    return (TRUE);
}

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "obj_loader/tinyobj_loader_c.h"
static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]) {
    float v10[3];
    float v20[3];
    float len2;

    v10[0] = v1[0] - v0[0];
    v10[1] = v1[1] - v0[1];
    v10[2] = v1[2] - v0[2];

    v20[0] = v2[0] - v0[0];
    v20[1] = v2[1] - v0[1];
    v20[2] = v2[2] - v0[2];

    N[0] = v20[1] * v10[2] - v20[2] * v10[1];
    N[1] = v20[2] * v10[0] - v20[0] * v10[2];
    N[2] = v20[0] * v10[1] - v20[1] * v10[0];

    len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
    if (len2 > 0.0f) {
        float len = (float)sqrt((double)len2);

        N[0] /= len;
        N[1] /= len;
    }
}

static float* LoadObjAndConvert(float bmin[3], float bmax[3], int *vertices_size, const char* filepath)
{
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t* materials = NULL;
    size_t num_materials;
    float *vertices;
    size_t data_len = 0;
    const char* data = read_file(filepath, &data_len);
    if (data == NULL) {
        exit(-1);
        /* return 0; */
    }
    printf("filesize: %d\n", (int)data_len);

    {
        unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
        int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials,
                                    &num_materials, data, data_len, flags);
        if (ret != TINYOBJ_SUCCESS) {
            return 0;
        }

        printf("# of shapes    = %d\n", (int)num_shapes);
        printf("# of materials = %d\n", (int)num_materials);

        bmin[0] = bmin[1] = bmin[2] = FLT_MAX;
        bmax[0] = bmax[1] = bmax[2] = -FLT_MAX;

        {

            size_t face_offset = 0;
            size_t i;

            /* Assume triangulated face. */
            size_t num_triangles = attrib.num_face_num_verts;
            size_t stride = 3; /* 3 = pos(3float) */


            vertices = (float*)malloc(sizeof(float) * stride * num_triangles * 3);
            *vertices_size = stride * num_triangles * 3;
            for (i = 0; i < attrib.num_face_num_verts; i++)
            {
                size_t f;
                assert(attrib.face_num_verts[i] % 3 ==
                       0); /* assume all triangle faces. */
                for (f = 0; f < (size_t)attrib.face_num_verts[i] / 3; f++)
                {
                    size_t k;
                    float v[3][3];
                    float n[3][3];
                    float c[3];
                    float len2;

                    tinyobj_vertex_index_t idx0 = attrib.faces[face_offset + 3 * f + 0];
                    tinyobj_vertex_index_t idx1 = attrib.faces[face_offset + 3 * f + 1];
                    tinyobj_vertex_index_t idx2 = attrib.faces[face_offset + 3 * f + 2];

                    for (k = 0; k < 3; k++)
                    {
                        int f0 = idx0.v_idx;
                        int f1 = idx1.v_idx;
                        int f2 = idx2.v_idx;
                        assert(f0 >= 0);
                        assert(f1 >= 0);
                        assert(f2 >= 0);

                        v[0][k] = attrib.vertices[3 * (size_t)f0 + k];
                        v[1][k] = attrib.vertices[3 * (size_t)f1 + k];
                        v[2][k] = attrib.vertices[3 * (size_t)f2 + k];
                        bmin[k] = (v[0][k] < bmin[k]) ? v[0][k] : bmin[k];
                        bmin[k] = (v[1][k] < bmin[k]) ? v[1][k] : bmin[k];
                        bmin[k] = (v[2][k] < bmin[k]) ? v[2][k] : bmin[k];
                        bmax[k] = (v[0][k] > bmax[k]) ? v[0][k] : bmax[k];
                        bmax[k] = (v[1][k] > bmax[k]) ? v[1][k] : bmax[k];
                        bmax[k] = (v[2][k] > bmax[k]) ? v[2][k] : bmax[k];
                    }

                    for (k = 0; k < 3; k++)
                    {
                        vertices[(3 * i + k) * stride + 0] = v[k][0];
                        vertices[(3 * i + k) * stride + 1] = v[k][1];
                        vertices[(3 * i + k) * stride + 2] = v[k][2];
                    }
                }

                face_offset += (size_t)attrib.face_num_verts[i];
            }
        }

        printf("bmin = %f, %f, %f\n", (double)bmin[0], (double)bmin[1],
               (double)bmin[2]);
        printf("bmax = %f, %f, %f\n", (double)bmax[0], (double)bmax[1],
               (double)bmax[2]);

        tinyobj_attrib_free(&attrib);
        tinyobj_shapes_free(shapes, num_shapes);
        tinyobj_materials_free(materials, num_materials);
    }
    return (vertices);
}

unsigned load_polygon(cJSON *objects, int object_index, t_union *un)
{
    t_polygon polygon_data;
    cJSON *polygon;
    t_object *obj = NULL;
    t_material material;

    polygon = cJSON_GetArrayItem(objects, object_index);

    if (!validate_json_polygon(polygon))
        return (FALSE);
    float min[3], max[3];
    float *vertices = NULL;
    int vertices_size;
    vertices = LoadObjAndConvert(min, max, &vertices_size, cJSON_GetObjectItem(polygon, FILEPATH)->valuestring);
    polygon_data.vertices = vertices;
    vec_set(&polygon_data.max, max[0], max[1], max[2]);
    vec_set(&polygon_data.min, min[0], min[1], min[2]);
    polygon_data.vertices_size =  vertices_size;
    material.color.r = 255;
    material.color.g = 0;
    material.color.b = 0;
    material.specular = 10;
    obj = create_polygon_node(&polygon_data, POLYGON, material.color);
    obj->material.specular = material.specular;
    un->objects = object_push_back(un->objects, obj);

    return (TRUE);
}