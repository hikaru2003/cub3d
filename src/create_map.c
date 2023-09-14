/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:38:58 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/14 15:08:00 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_map(t_data *data)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	data->map = (char **)malloc(sizeof(char *) * (data->max_y + 1));
	if (!data->map)
		print_error("bad_alloc");
	while (j < data->max_y)
	{
		data->map[j] = (char *)malloc(sizeof(char) * (data->max_x + 1));
		if (!data->map[j])
			print_error("bad_alloc");
		i = 0;
		while (i < data->max_x)
		{
			data->map[j][i] = ' ';
			i++;
		}
		data->map[j][i] = '\0';
		j++;
	}
	data->map[j] = NULL;
}

void	skip_elements(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 8)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
}

void	create_map(t_data *data, char *filename)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	fd = open(filename, O_RDONLY);
	i = 0;
	j = 0;
	init_map(data);
	skip_elements(data, fd);
	while (j < data->max_y)
	{
		line = get_next_line(fd);
		i = 0;
		while (line[i] != '\n' && line[i] != '\0')
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				if (data->direction != -1)
					print_error("duplicate player position");
				data->pos_x = i;
				data->pos_y = j;
				if (line[i] == 'N')
					data->direction = NORTH;
				else if (line[i] == 'S')
					data->direction = SOUTH;
				else if (line[i] == 'E')
					data->direction = EAST;
				else if (line[i] == 'W')
					data->direction = WEST;
			}
			data->map[j][i] = line[i];
			i++;
		}
		free(line);
		j++;
	}
	close (fd);
}