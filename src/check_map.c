/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:37:31 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/20 15:17:08 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_surroundings(t_data *data, int i, int j)
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
	while (j < data->max_y)
	{
		i = 0;
		while (i < data->max_x)
		{
			if (data->map[j][i] == ' ')
				check_surroundings(data, i, j);
			i++;
		}
		j++;
	}
}
