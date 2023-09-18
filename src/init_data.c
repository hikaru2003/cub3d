/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:29:02 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/18 19:23:13 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		print_error("bad_alloc");
	data->direction = -1;
	data->max_x = 0;
	data->max_y = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->xpm_width = 0;
	data->xpm_height = 0;
	data->path = (char **)malloc(sizeof(char *) * 4);
	if (!data->path)
		print_error("bad_alloc");
	return (data);
}