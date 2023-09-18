/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:01:19 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/18 21:54:55 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	go_straight(t_data *data)
{
	// printf("go straight\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x, (int)data->pos_x, data->pos_y - STEP, (int)(data->pos_y - STEP));
	if (data->map[(int)(data->pos_y - STEP)][(int)data->pos_x] != '1')
		data->pos_y -= STEP;
}

void	go_back(t_data *data)
{
	// printf("go back\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x, (int)data->pos_x, data->pos_y + STEP, (int)(data->pos_y + STEP));
	if (data->map[(int)(data->pos_y + STEP)][(int)data->pos_x] != '1')
		data->pos_y += STEP;
}

void	go_left(t_data *data)
{
	// printf("go left\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x - STEP, (int)(data->pos_x - STEP), data->pos_y, (int)(data->pos_y));
	if (data->map[(int)data->pos_y][(int)(data->pos_x - STEP)] != '1')
		data->pos_x -= STEP;
}

void	go_right(t_data *data)
{
	// printf("go right\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x + STEP, (int)(data->pos_x + STEP), data->pos_y, (int)(data->pos_y));
	if (data->map[(int)data->pos_y][(int)(data->pos_x + STEP)] != '1')
		data->pos_x += STEP;
}

void	culc_distance(t_data *data, double angle)
{
	double	dx;
	double	dy;
	double	x_step;
	double	y_step;
	int		tile_step_x;
	int		tile_step_y;
	double	x_intercept;
	double	y_intercept;
	

	if (angle > 180)
	{
		dy = (int)data->pos_y - data->pos_y;
		y_step = -1 / tan(angle * M_PI / 180);
		tile_step_y = -1;
	}
	else
	{
		dy = (int)data->pos_y + 1 - data->pos_y;
		y_step = -1 / tan(angle * M_PI / 180);
		tile_step_y = 1;
	}
	if (angle < 90 || angle > 270)
	{
		dx = (int)data->pos_x + 1 - data->pos_x;
		x_step = -tan(angle * M_PI / 180);
		tile_step_x = 1;
	}
	else
	{
		dx = (int)data->pos_x - data->pos_x;
		x_step = -tan(angle * M_PI / 180);
		tile_step_x = -1;
	}
	x_intercept = data->pos_x + dx - dy / tan(angle * M_PI / 180);
	y_intercept = data->pos_y + dy + dx / tan(angle * M_PI / 180);
}

void	update_display(t_data *data, int index)
{
	// double	shift_angle;
	// double	start_angle;
	// double	end_angle;

	// shift_angle = (double)VIEW_ANGLE / DISPLAY_X;
	// start_angle = data->direction - (double)VIEW_ANGLE / 2;
	// end_angle = data->direction + (double)VIEW_ANGLE / 2;
	// while (start_angle <= end_angle)
	// {
	// 	culc_distance(data, start_angle);
	// 	start_angle += shift_angle;
	// }



	// after calculate distance, (x, y) position, direction->壁が東西南北どれかわかる
	// int	x = data->xpm_width * (data->pos_x - (int)data->pos_x);
	// int	y = data->xpm_height * (data->pos_y - (int)data->pos_y);
	// int	pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
	// char	*mlx_data_addr = mlx_get_data_addr(data->north_img, &data->bits_per_pixel, &data->line_length, &data->endian);


	int	i = 0;
	int	j = 0;
	int	x = 0;
	int	y = 0;
	int	pos = 0;
	char	*mlx_data_addr;
	while (j < DISPLAY_Y)
	{
		i = 0;
		x = 0;
		while (i < DISPLAY_X)
		{
			pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
			// 壁はランダムに表示
			mlx_data_addr = mlx_get_data_addr(data->direction_img[index], &data->bits_per_pixel, &data->line_length, &data->endian);
			data->display[j][i] = *(unsigned int *)(mlx_data_addr + pos);
			i++;
			x++;
			if (x == data->xpm_width)
				x = 0;
		}
		j++;
		y++;
		if (y == data->xpm_height)
			y = 0;
	}
}

int	next_frame(int keycode, t_data *data)
{
	// printf("before> pos_x: %f, pos_y: %f\n", data->pos_x, data->pos_y);
	if (keycode == ESC)
	{
		// ft_destroy(data)と同じ内容？
		mlx_destroy_window(data->mlx, data->win);
		// free data, etc...
		exit (0);
	}
	// go front
	if (keycode == UP_ARROW || keycode == KEY_W)
		go_straight(data);
	// go back
	if (keycode == DOWN_ARROW || keycode == KEY_S)
		go_back(data);
	// go left
	if (keycode == KEY_A)
		go_left(data);
	// go right
	if (keycode == KEY_D)
		go_right(data);
	// turn left
	if (keycode == LEFT_ARROW)
		data->direction	-= ANGLE;
	// turn right
	if (keycode == RIGHT_ARROW)
		data->direction += ANGLE;
	// printf("after> pos_x: %f, pos_y: %f\n", data->pos_x, data->pos_y);
	update_display(data, rand() % 4);
	return (0);
}
