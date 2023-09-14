/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:10:25 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/11 20:06:33 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_path(char *line, int index, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		print_error("path is missing");
	data->path[index] = ft_strdup(&line[i]);
}

void	check_rgb(char *line, int *color, int i)
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

void	check_color(char *line, int identifier, t_data *data)
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
		if (i == 0 && line[0] == 'N' && line[1] == 'O')
			check_path(&line[2], i, data);
		else if (i == 1 && line[0] == 'S' && line[1] == 'O')
			check_path(&line[2], i, data);
		else if (i == 2 && line[0] == 'W' && line[1] == 'E')
			check_path(&line[2], i, data);
		else if (i == 3 && line[0] == 'E' && line[1] == 'A')
			check_path(&line[2], i, data);
		else if ((i == 4 || i == 7) && line[0] == '\n')
			;
		else if (i == 5 && line[0] == 'F')
			check_color(&line[1], 'F', data);
		else if (i == 6 && line[0] == 'C')
			check_color(&line[1], 'C', data);
		else
			print_error("element is incorrect");
		free(line);
		i++;
	}
}

void	check_map_elements(char *line, int line_len)
{
	int	i;

	i = 0;
	while (i < line_len)
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ' ||
			line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			i++;
		else
		{
			printf("line len = %d\n", line_len);
			printf("%s", line);
			print_error("map element is incorrect");
		}
	}	
}

void	get_map_info(int fd, t_data *data)
{
	char	*line;
	int		line_len;
	
	line_len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			line[ft_strchr(line, '\n') - line] = '\0';
		line_len = ft_strlen(line);
		if (ft_strlen(line) == 0)
			print_error("map is missing");
		if (line_len > data->max_x)
			data->max_x = line_len;
		check_map_elements(line, line_len);
		data->max_y++;
		free(line);
	}
}

void	check_file(char *filename, t_data *data)
{
	char	*dot;
	int		fd;

	dot = ft_strchr(filename, '.');
	if (!dot)
		print_error("filename incorrect");
	if (ft_strcmp(dot, ".cub"))
		print_error("filename incorrect");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("cannot open file");
	check_elements(fd, data);
	get_map_info(fd, data);
	close (fd);
}
