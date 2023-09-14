/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:44:54 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/14 15:11:54 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_data(t_data *data)
{
	printf("max_x: %d\n", data->max_x);
	printf("max_y: %d\n", data->max_y);
	printf("map:\n");
	for (int i = 0; i < data->max_y; i++)
	{
		printf("%s\n", data->map[i]);
	}
	printf("player_x: %d\n", data->pos_x);
	printf("player_y: %d\n", data->pos_y);
	printf("player_dir: %d\n", data->direction);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	if (argc != 2)
		print_error("please input a map");
	data = init_data();
	check_file(argv[1], data);
	create_map(data, argv[1]);
	// print_data(data);
	// check_map(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, DISPLAY_X, DISPLAY_Y, "cub3d");
	data->img = mlx_new_image(data->mlx, DISPLAY_X, DISPLAY_X);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1, next_frame, data);
	mlx_hook(data->win, 17, 1, ft_destroy, data);
	mlx_loop_hook(data->mlx, draw_map, data);
	// mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}

// __attribute__((destructor))
// static void	destructor(void){
// 	system("leaks -q cub3d");
// }
