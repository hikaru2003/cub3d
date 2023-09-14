/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:29:02 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/11 20:52:49 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		print_error("bad_alloc");
	data->max_x = 0;
	data->max_y = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->direction = -1;
	data->path = (char **)malloc(sizeof(char *) * 4);
	if (!data->path)
		print_error("bad_alloc");
	return (data);
}