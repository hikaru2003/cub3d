/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:37:31 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/20 16:26:42 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_rows(t_data *data)
{
	int	y;
	int	start;
	int	end;

	y = 0;
	start = 0;
	end = data->max_x - 1;
	while (y < data->max_y)
	{
		start = 0;
		end = data->max_x - 1;
		while (data->map[y][start] == ' ')
			start++;
		if (data->map[y][start] != '1')
			print_error("map is not closed");
		while (data->map[y][end] == ' ')
			end--;
		if (data->map[y][end] != '1')
			print_error("map is not closed");
		y++;
	}
}

void	check_columns(t_data *data)
{
	int	x;
	int	start;
	int	end;

	x = 0;
	start = 0;
	end = data->max_y - 1;
	while (x < data->max_x)
	{
		start = 0;
	end = data->max_y - 1;
		while (data->map[start][x] == ' ')
			start++;
		if (data->map[start][x] != '1')
			print_error("map is not closed");
		while (data->map[end][x] == ' ')
			end--;
		if (data->map[end][x] != '1')
			print_error("map is not closed");
		x++;
	}
}

void	is_surrounded_by_wall(t_data *data, int i, int j)
{
	if (j > 0 && data->map[j - 1][i] != '1' && data->map[j - 1][i] != ' ')
		print_error("map is not closed");
	// j + 1 == data->max_y - 1 がjのが最大
	if (j < data->max_y - 1 && data->map[j + 1][i] != '1'
		&& data->map[j + 1][i] != ' ')
		print_error("map is not closed");
	if (i > 0 && data->map[j][i - 1] != '1' && data->map[j][i - 1] != ' ')
		print_error("map is not closed");
	// i + 1 == data->max_x - 1 がiのが最大
	if (i < data->max_x - 1 && data->map[j][i + 1] != '1'
		&& data->map[j][i + 1] != ' ')
		print_error("map is not closed");
}

void	check_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_rows(data);
	check_columns(data);
	while (j < data->max_y)
	{
		i = 0;
		while (i < data->max_x)
		{
			if (data->map[j][i] == ' ')
				is_surrounded_by_wall(data, i, j);
			i++;
		}
		j++;
	}
}
