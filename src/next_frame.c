/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:01:19 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/14 15:12:31 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	go_straight(t_data *data)
{
	if (data->map[data->pos_y - 1][data->pos_x] == '0')
		data->pos_y--;
}

void	go_back(t_data *data)
{
	if (data->map[data->pos_y + 1][data->pos_x] == '0')
		data->pos_y++;
}

void	go_left(t_data *data)
{
	if (data->map[data->pos_y][data->pos_x - 1] == '0')
		data->pos_x--;
}

void	go_right(t_data *data)
{
	if (data->map[data->pos_y][data->pos_x + 1] == '0')
		data->pos_x++;
}

void	update_display(t_data *data)
{
	
}

int	next_frame(int keycode, t_data *data)
{
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
	// update_display(data);
	return (0);
}
