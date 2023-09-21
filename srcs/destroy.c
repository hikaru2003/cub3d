/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:10:00 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/21 22:11:02 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (!data->map)
		return ;
	while (i <= data->max_y)
	{
		free(data->map[i]);
		// if (data->map[i])
		// {
		// 	printf("i = %d\n", i);
		// }
		i++;
	}
	printf("before\n");
	free(data->map);
	printf("after\n");
	if (data->map == NULL)
		printf("map is freed\n");
}

void	free_path(t_data *data)
{
	int	i;

	i = 0;
	if (!data->path)
		return ;
	while (i < 4)
	{
		if (data->path[i])
			free(data->path[i]);
		i++;
	}
	free(data->path);
}

int	ft_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	// free data, etc...
	// free_map(data);
	// free_path(data);
	// free(data);
	exit (1);
}
