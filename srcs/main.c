/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:44:54 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/27 20:30:15 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		print_error("please input a map");
	data = init_data();
	data->mlx = mlx_init();
	check_file(argv[1], data);
	create_map(argv[1], data);
	check_map(data);
	reset_display(data);
	culc_distance(data);
	data->win = mlx_new_window(data->mlx, DISPLAY_X, DISPLAY_Y, "cub3d");
	data->img = mlx_new_image(data->mlx, DISPLAY_X, DISPLAY_X);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1, next_frame, data);
	mlx_hook(data->win, 17, 1, ft_destroy, data);
	mlx_loop_hook(data->mlx, draw_map, data);
	mlx_loop(data->mlx);
	return (0);
}

// __attribute__((destructor))
// static void	destructor(void){
// 	system("leaks -q cub3d");
// }
