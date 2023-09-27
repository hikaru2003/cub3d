/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:01:19 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/27 21:57:04 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	go_straight(t_data *data)
{
	double	step_x;
	double	step_y;

	step_x = (STEP + 0.2) * cos(data->direction * M_PI / 180) + data->pos_x;
	step_y = (STEP + 0.2) * sin(data->direction * M_PI / 180) + data->pos_y;
	if (data->map[(int)step_y][(int)step_x] != '1')
	{
		step_x = STEP * cos(data->direction * M_PI / 180);
		step_y = STEP * sin(data->direction * M_PI / 180);
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
}

void	go_back(t_data *data)
{
	double	step_x;
	double	step_y;
	double	direction;

	direction = data->direction + 180;
	step_x = (STEP + 0.2) * cos(direction * M_PI / 180) + data->pos_x;
	step_y = (STEP + 0.2) * sin(direction * M_PI / 180) + data->pos_y;
	if (data->map[(int)step_y][(int)step_x] != '1')
	{
		step_x = STEP * cos((data->direction + 180) * M_PI / 180);
		step_y = STEP * sin((data->direction + 180) * M_PI / 180);
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
}

void	go_left(t_data *data)
{
	double	step_x;
	double	step_y;
	double	direction;

	direction = data->direction - 90;
	step_x = (STEP + 0.2) * cos(direction * M_PI / 180) + data->pos_x;
	step_y = (STEP + 0.2) * sin(direction * M_PI / 180) + data->pos_y;
	if (data->map[(int)step_y][(int)step_x] != '1')
	{
		step_x = STEP * cos((data->direction - 90) * M_PI / 180);
		step_y = STEP * sin((data->direction - 90) * M_PI / 180);
		data->pos_x += step_x;
		data->pos_y += step_y;
	}
}

void	go_right(t_data *data)
{
	double	step_x;
	double	step_y;
	double	direction;

	direction = data->direction + 90;
	step_x = (STEP + 0.2) * cos(direction * M_PI / 180) + data->pos_x;
	step_y = (STEP + 0.2) * sin(direction * M_PI / 180) + data->pos_y;
	if (data->map[(int)step_y][(int)step_x] != '1')
	{
		step_x = STEP * cos((data->direction + 90) * M_PI / 180);
		step_y = STEP * sin((data->direction + 90) * M_PI / 180);
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

// result_data.height_ratio = atan(0.5 / result_data.distance) / M_PI * 180 / (double)VIEW_ANGLE_Y * (double) 2;
// result_data.height	= (int)DISPLAY_HALF * result_data.height_ratio;
// result_data.height_per_pixel = (float)result_data.height / (float)(data->xpm_height / 2);

void	update_display(t_data *data, int index, t_status status)
{
	int		j;
	t_coor	cor;
	int		pos;
	char	*mlx_data_addr;
	int		current_pixel;

	cor.x = (int)(status.pos * data->xpm_width);
	cor.y = 0;
	current_pixel = 0;
	j = DISPLAY_HALF - status.height;
	while (j < DISPLAY_HALF + status.height)
	{
		pos = (cor.y * data->line_length + cor.x * (data->bits_per_pixel / 8));
		mlx_data_addr = mlx_get_data_addr(data->direction_img[status.dir],
				&data->bits_per_pixel, &data->line_length, &data->endian);
		if (0 <= j && j < DISPLAY_Y)
			data->display[j][index] = *(unsigned int *)(mlx_data_addr + pos);
		j++;
		while (((j - DISPLAY_HALF + status.height) / status.height_per_pixel) > current_pixel + 1)
		{
			current_pixel++;
			cor.y++;
		}
		if (cor.y >= data->xpm_height)
			cor.y = data->xpm_height - 1;
	}
}

int	next_frame(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		ft_destroy(data);
		// free data, etc...
		exit (0);
	}
	if (keycode == KEY_W)
		go_straight(data);
	if (keycode == KEY_S)
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
			data->direction -= ANGLE;
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
