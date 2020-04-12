#include "rtv1.h"

t_vec           apply_rotate_matrix(t_vec vec, t_matrix *matrix)
{
    t_matrix    vector;
    t_matrix    transformed;
    t_vec       result_vector;

    vector = matrix_allocate(3, 1);
    vector.data[0][0] = vec.x;
    vector.data[1][0] = vec.y;
    vector.data[2][0] = vec.z;
    transformed = matrix_mul(matrix, &vector);
    vec_set(&result_vector, (float) transformed.data[0][0],
    (float) transformed.data[1][0], (float) transformed.data[2][0]);
    matrix_deallocate(&vector);
    matrix_deallocate(&transformed);
    return (result_vector);

}