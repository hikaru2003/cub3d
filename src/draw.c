/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:17:00 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/11 20:23:12 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_one_pixel(t_data *data, int x, int y)
{
	// if (y < DISPLAY_Y / 2)
	// 	my_mlx_pixel_put(data, x, y, data->ceiling_rgb);
	// else
	// 	my_mlx_pixel_put(data, x, y, data->floor_rgb);
	my_mlx_pixel_put(data, x, y, data->display[y][x]);
}

int	draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < DISPLAY_Y)
	{
		x = 0;
		while (x < DISPLAY_X)
		{
			draw_one_pixel(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
