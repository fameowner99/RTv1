/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:40:51 by vmiachko          #+#    #+#             */
/*   Updated: 2019/07/13 14:41:40 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include "parser.h"
void	initialize(t_union *un)
{
    un->objects = NULL;
    un->lights = NULL;
    vec_set(&un->camera.basis.position, 5, 0, -10);
	vec_set(&un->camera.basis.up, 0, 1, 0);
	vec_set(&un->camera.basis.look_at, 0, 0 , 1);
    g_background_color.r = BACKGROUND_COLOR_R;
    g_background_color.g = BACKGROUND_COLOR_G;
    g_background_color.b = BACKGROUND_COLOR_B;
    un->mouse.is_clicked = FALSE;
    un->mouse.clicked_x = 0;
    un->mouse.clicked_y = 0;
    un->camera.matrix = matrix_allocate(3, 3);
    un->camera.matrix.data[0][0] = 1;
    un->camera.matrix.data[1][1] = 1;
    un->camera.matrix.data[2][2] = 1;
}

#if (_MSC_VER)
# undef main
#endif


int		main(int argc, char *argv[])
{
	t_union un;

	initialize(&un);
	if (argc != 2)
	{
        ft_printf(RED"Usage: %s scene.rt\n\n"RESET, argv[0]);
        return 1;
    }
	if (parse_arguments(argc, argv, &un) == FALSE)
    {
        ft_printf(BLUE"%s contains error(s).\n\n"RESET, argv[1]);
	    ft_printf(GREEN"Some hints:\n1) Scene must contain .rt extension\n2) Check json format in any online json validator\n"RESET);
	    return 1;
    }
	rt(&un);
	return (0);
}