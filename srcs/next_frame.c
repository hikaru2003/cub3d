/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:01:19 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/25 13:16:51 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	go_straight(t_data *data)
{
	// printf("go straight\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x, (int)data->pos_x, data->pos_y - STEP, (int)(data->pos_y - STEP));
	double	step_x;
	double	step_y;

	step_x = STEP * cos(data->direction * M_PI / 180);
	step_y = STEP * sin(data->direction * M_PI / 180);
	if (data->map[(int)(data->pos_y + step_y)][(int)(data->pos_x + step_x)] != '1')
	{
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
}

void	go_back(t_data *data)
{
	// printf("go back\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x, (int)data->pos_x, data->pos_y + STEP, (int)(data->pos_y + STEP));
	double	step_x;
	double	step_y;

	step_x = STEP * cos((data->direction + 180) * M_PI / 180);
	step_y = STEP * sin((data->direction + 180) * M_PI / 180);
	if (data->map[(int)(data->pos_y + step_y)][(int)(data->pos_x + step_x)] != '1')
	{
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
}

void	go_left(t_data *data)
{
	// printf("go left\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x - STEP, (int)(data->pos_x - STEP), data->pos_y, (int)(data->pos_y));
	double	step_x;
	double	step_y;

	step_x = STEP * cos((data->direction - 90) * M_PI / 180);
	step_y = STEP * sin((data->direction - 90) * M_PI / 180);
	if (data->map[(int)(data->pos_y + step_y)][(int)(data->pos_x + step_x)] != '1')
	{
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
}

void	go_right(t_data *data)
{
	// printf("go right\n");
	// printf("x=%f -> %d, y=%f -> %d\n", data->pos_x + STEP, (int)(data->pos_x + STEP), data->pos_y, (int)(data->pos_y));
	double	step_x;
	double	step_y;

	step_x = STEP * cos((data->direction + 90) * M_PI / 180);
	step_y = STEP * sin((data->direction + 90) * M_PI / 180);
	if (data->map[(int)(data->pos_y + step_y)][(int)(data->pos_x + step_x)] != '1')
	{
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
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

void	update_display(t_data *data, int index, t_status status)
{
	int	i = 0;
	int	j = 0;
	int	x = (int)(status.pos * data->xpm_width);
	int	y = 0;
	int	pos = 0;
	char	*mlx_data_addr;
	int	half_y = DISPLAY_Y / 2;
	int height = (int)MAX_WALL_HEIGHT - MIN_WALL_HEIGHT * status.distance / data->max_y;
	int	count = 0;
	int		current_pixel = 0;
	float	next_pixel = 0;
	
	current_pixel = 0;
	j = half_y - (height / 2);
	while (j < half_y + (height / 2))
	{
		pos = (y * data->line_length + x * (data->bits_per_pixel / 8));
		mlx_data_addr = mlx_get_data_addr(data->direction_img[status.dir], &data->bits_per_pixel, &data->line_length, &data->endian);
		if (0 <= j && j < DISPLAY_X)
			data->display[j][index] = *(unsigned int *)(mlx_data_addr + pos);
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
}

int	next_frame(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		// ft_destroy(data)と同じ内容？
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
	{
		if (data->direction - ANGLE < 0)
			data->direction = 360 + data->direction - ANGLE;
		else
			data->direction	-= ANGLE;
	}
	if (keycode == RIGHT_ARROW)
	{
		if (data->direction + ANGLE > 360)
			data->direction = 360 - data->direction + ANGLE;
		else
			data->direction += ANGLE;
	}
	reset_display(data);
	culc_distance(data);
	return (0);
}
