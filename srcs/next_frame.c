/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:01:19 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/21 18:43:01 by hikaru           ###   ########.fr       */
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

void	reset_display(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < DISPLAY_Y / 2)
	{
		x = 0;
		while (x < DISPLAY_X)
		{
			data->display[y][x] = data->ceiling_rgb;
			x++;
		}
		y++;
	}
	while (y < DISPLAY_Y)
	{
		x = 0;
		while (x < DISPLAY_X)
		{
			data->display[y][x] = data->floor_rgb;
			x++;
		}
		y++;
	}
}

void	update_display(t_data *data, int index)
{
	int	i = 0;
	int	j = 0;
	int	x = 0;
	int	y = 0;
	int	pos = 0;
	char	*mlx_data_addr;
	
	// after calculate distance, (x, y) position, direction->壁が東西南北どれかわかる
	// int	x = data->xpm_width * (data->pos_x - (int)data->pos_x);
	// int	y = data->xpm_height * (data->pos_y - (int)data->pos_y);
	// int	pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
	// char	*mlx_data_addr = mlx_get_data_addr(data->north_img, &data->bits_per_pixel, &data->line_length, &data->endian);

	// 全画面に壁を表示させる、奥行きはない
	// 
	// while (j < DISPLAY_Y)
	// {
	// 	i = 0;
	// 	x = 0;
	// 	while (i < DISPLAY_X)
	// 	{
	// 		pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
	// 		// 壁はランダムに表示
	// 		mlx_data_addr = mlx_get_data_addr(data->direction_img[index], &data->bits_per_pixel, &data->line_length, &data->endian);
	// 		data->display[j][i] = *(unsigned int *)(mlx_data_addr + pos);
	// 		i++;
	// 		if (i % 2 == 0)
	// 			x++;
	// 		// x++;
	// 		if (x == data->xpm_width)
	// 			x = 0;
	// 	}
	// 	j++;
	// 	if (j % 2 == 0)
	// 		y++;
	// 	// y++;
	// 	if (y == data->xpm_height)
	// 		y = 0;
	// }

	// 奥行きありの壁を表示させる
	int	half_y = DISPLAY_Y / 2;
	int height = DISPLAY_Y * 3 / 4;
	int	count = 0;
	int		current_pixel = 0;
	float	next_pixel = 0;
	j = half_y;
	while (i < DISPLAY_X / 2)
	{
		count = 0;
		y = 0;
		current_pixel = 0;
		j = half_y - (height / 2);
		while (j < half_y + (height / 2))
		{
			pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
			// 壁はランダムに表示
			mlx_data_addr = mlx_get_data_addr(data->direction_img[index], &data->bits_per_pixel, &data->line_length, &data->endian);
			data->display[j][i] = *(unsigned int *)(mlx_data_addr + pos);
			j++;
			count++;
			next_pixel = count / ((float)height / data->xpm_height);
			if ((int)next_pixel > current_pixel + 1)
			{
				current_pixel++;
				y++;
			}
			if (y == data->xpm_height) //万が一範囲外のピクセルを参照した場合の処理
				y = data->xpm_height - 1;
		}
		if (i % 4 == 0)
			height--;
		if (height < DISPLAY_Y / 4)
			height = DISPLAY_Y * 3 / 4;
		i++;
		if (i % 2 == 0)
			x++;
		if (x == data->xpm_width)
		{
			x = 0;
			index = rand() % 4;
		}
	}
	current_pixel = 0;
	while (i < DISPLAY_X)
	{
		count = 0;
		y = 0;
		current_pixel = 0;
		j = half_y - (height / 2);
		while (j < half_y + (height / 2))
		{
			pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
			// 壁はランダムに表示
			mlx_data_addr = mlx_get_data_addr(data->direction_img[index], &data->bits_per_pixel, &data->line_length, &data->endian);
			data->display[j][i] = *(unsigned int *)(mlx_data_addr + pos);
			j++;
			count++;
			next_pixel = count / ((float)height / data->xpm_height);
			if ((int)next_pixel > current_pixel + 1)
			{
				current_pixel++;
				y++;
			}
			if (y == data->xpm_height) //万が一範囲外のピクセルを参照した場合の処理
				y = data->xpm_height - 1;
		}
		if (i % 4 == 0)
			height++;
		if (height == DISPLAY_Y * 3 / 4)
			height = DISPLAY_Y / 4;
		i++;
		if (i % 2 == 0)
			x++;
		if (x == data->xpm_width)
		{
			x = 0;
			index = rand() % 4;
		}
	}
}

int	next_frame(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		// ft_destroy(data)と同じ内容？
		printf("here\n");
		ft_destroy(data);
		// free data, etc...
		exit (0);
	}
	if (keycode == UP_ARROW || keycode == KEY_W)
		go_straight(data);
	if (keycode == DOWN_ARROW || keycode == KEY_S)
		go_back(data);
	if (keycode == KEY_A)
		go_left(data);
	if (keycode == KEY_D)
		go_right(data);
	if (keycode == LEFT_ARROW)
		data->direction	-= ANGLE;
	if (keycode == RIGHT_ARROW)
		data->direction += ANGLE;
	reset_display(data);
	update_display(data, rand() % 4);
	return (0);
}
