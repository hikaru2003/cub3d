/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:39:00 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/28 11:41:42 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_path(char *line, int index, t_data *data, void *img)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		print_error("path is missing");
	if (ft_strchr(line, '\n'))
		line[ft_strchr(line, '\n') - line] = '\0';
	data->path[index] = ft_strdup(&line[i]);
	if (!data->path[index])
		print_error("bad_alloc");
	data->direction_img[index] = mlx_xpm_file_to_image(data->mlx,
			data->path[index], &(data->xpm_width), &(data->xpm_height));
	if (!data->direction_img[index])
		print_error("cannot open xpm file");
}

static void	check_rgb(char *line, int *color, int i)
{
	int	rgb;

	rgb = 0;
	if (line[0] < '0' || line[0] > '9')
		print_error("rgb is missing");
	rgb = ft_atoi(line);
	if (rgb < 0 || rgb > 255)
		print_error("rgb out of range");
	if (i == 0)
		*color += rgb * 256 * 256;
	else if (i == 1)
		*color += rgb * 256;
	else
		*color += rgb;
}

static void	check_color(char *line, int identifier, t_data *data)
{
	int	i;
	int	color;

	i = 0;
	color = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		print_error("color is missing");
	check_rgb(&line[i], &color, 0);
	i += ft_strchr(&line[i], ',') - &line[i] + 1;
	check_rgb(&line[i], &color, 1);
	i += ft_strchr(&line[i], ',') - &line[i] + 1;
	check_rgb(&line[i], &color, 2);
	if (identifier == 'F')
		data->floor_rgb = color;
	if (identifier == 'C')
		data->ceiling_rgb = color;
}

static void	check_path_or_color(char *line, int i, t_data *data)
{
	if (i == 0 && line[0] == 'N' && line[1] == 'O')
		check_path(&line[2], i, data, &data->north_img);
	else if (i == 1 && line[0] == 'S' && line[1] == 'O')
		check_path(&line[2], i, data, &data->south_img);
	else if (i == 2 && line[0] == 'W' && line[1] == 'E')
		check_path(&line[2], i, data, &data->west_img);
	else if (i == 3 && line[0] == 'E' && line[1] == 'A')
		check_path(&line[2], i, data, &data->east_img);
	else if ((i == 4 || i == 7) && line[0] == '\n')
		;
	else if (i == 5 && line[0] == 'F')
		check_color(&line[1], 'F', data);
	else if (i == 6 && line[0] == 'C')
		check_color(&line[1], 'C', data);
	else
		print_error("element is incorrect");
}

void	check_elements(int fd, t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 8)
	{
		line = get_next_line(fd);
		if (!line)
			print_error("element is missing");
		check_path_or_color(line, i, data);
		free(line);
		i++;
	}
}
