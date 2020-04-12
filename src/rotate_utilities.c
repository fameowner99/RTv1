#include "rtv1.h"

void    rotate_camera(t_union *un)
{
    int curr_x;
    int curr_y;
    float angle_x;
    float angle_y;
    t_matrix matrix;
    t_matrix result_matrix;

    SDL_GetMouseState(&curr_x, &curr_y);
    angle_x = (float) (curr_x - un->mouse.clicked_x) / W_WIDTH * 180;
    angle_y = (float) (curr_y - un->mouse.clicked_y) / W_HEIGHT * 180;
    matrix = get_rotate_matrix(angle_x, angle_y);
    result_matrix = matrix_mul(&un->camera.matrix, &matrix);
    matrix_deallocate(&un->camera.matrix);
    matrix_deallocate(&matrix);
    un->camera.matrix = result_matrix;
    update_camera_vectors(un);
    draw(un);
}

void                set_rotate_x_matrix(t_matrix *matrix, float angle)
{
    double           radians;

    radians = angle * M_PI / 180.;

    matrix->data[0][0] = 1;
    matrix->data[0][1] = 0;
    matrix->data[0][2] = 0;
    matrix->data[1][0] = 0;
    matrix->data[1][1] = cos(radians);
    matrix->data[1][2] = sin(radians);
    matrix->data[2][0] = 0;
    matrix->data[2][1] = -sin(radians);
    matrix->data[2][2] = cos(radians);
}

void                set_rotate_y_matrix(t_matrix *matrix, float angle)
{
    double           radians;

    radians = angle * M_PI / 180.;
    matrix->data[0][0] = cos(radians);
    matrix->data[0][1] = 0;
    matrix->data[0][2] = -sin(radians);
    matrix->data[1][0] = 0;
    matrix->data[1][1] = 1;
    matrix->data[1][2] = 0;
    matrix->data[2][0] = sin(radians);
    matrix->data[2][1] = 0;
    matrix->data[2][2] = cos(radians);
}

t_matrix            get_rotate_matrix(float angle_x, float angle_y)
{
    t_matrix        rotate_x;
    t_matrix        rotate_y;
    t_matrix        result_matrix;

    rotate_x = matrix_allocate(3, 3);
    rotate_y = matrix_allocate(3, 3);
    set_rotate_x_matrix(&rotate_x, angle_y);
    set_rotate_y_matrix(&rotate_y, angle_x);
    result_matrix = matrix_mul(&rotate_x, &rotate_y);
    matrix_deallocate(&rotate_x);
    matrix_deallocate(&rotate_y);
    return (result_matrix);
}