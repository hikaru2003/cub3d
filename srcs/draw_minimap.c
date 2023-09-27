/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:36:12 by hmorisak          #+#    #+#             */
/*   Updated: 2023/09/27 19:36:25 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_pixel(t_data *data, int i, int j, int color)
{
	int	start_x;
	int	max_x;
	int	max_y;

	start_x = i;
	max_x = i + MINIMAP_PIXEL;
	max_y = j + MINIMAP_PIXEL;
	while (j < max_y)
	{
		i = start_x;
		while (i < max_x)
		{
			data->display[j][i] = color;
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_data *data, t_coor start, t_coor end)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = start.x;
	while (start.y < end.y)
	{
		i = 0;
		x = start.x;
		while (x < end.x)
		{
			if (data->map[start.y][x] == '1')
				draw_pixel(data, i * MINIMAP_PIXEL + 20, j * MINIMAP_PIXEL + 20, 0xE7E7E7);
			else
				draw_pixel(data, i * MINIMAP_PIXEL + 20, j * MINIMAP_PIXEL + 20, 0x000080);
			if (x == (int)data->pos_x && start.y == (int)data->pos_y)
				draw_pixel(data, i * MINIMAP_PIXEL + 20, j * MINIMAP_PIXEL + 20, 0x00FF0000);
			i++;
			x++;
		}
		j++;
		start.y++;
	}
}

void	draw_part_of_minimap(t_data *data, int center_x, int center_y)
{
	t_coor	start;
	t_coor	end;
	t_coor	pos;

	pos.x = (int)data->pos_x;
	pos.y = (int)data->pos_y;
	start.x = pos.x - center_x;
	start.y = pos.y - center_y;
	end.x = pos.x + center_x;
	end.y = pos.y + center_y;
	if (pos.x < center_x)
	{
		start.x = 0;
		end.x = center_x * 2;
	}
	if (pos.x > data->max_x - center_x)
	{
		start.x = data->max_x - center_x * 2;
		end.x = data->max_x;
	}
	if (pos.y < center_y)
	{
		start.y = 0;
		end.y = center_y * 2;
	}
	if (pos.y > data->max_y - center_y)
	{
		start.y = data->max_y - center_y * 2;
		end.y = data->max_y;
	}
	draw_minimap(data, start, end);
}

void	update_minimap(t_data *data)
{
	t_coor	start;
	t_coor	end;
	
	if (data->max_x * MINIMAP_PIXEL > DISPLAY_X / 10 || data->max_y * MINIMAP_PIXEL > DISPLAY_Y / 5)
		draw_part_of_minimap(data, DISPLAY_X / 200, DISPLAY_Y / 100);
	else
	{
		start.x = 0;
		start.y = 0;
		end.x = data->max_x;
		end.y = data->max_y;
		draw_minimap(data, start, end);
	}
}
