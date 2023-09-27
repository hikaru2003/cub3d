/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   culc_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by akazuki           #+#    #+#             */
/*   Updated: 2023/09/27 21:54:21 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	check_map_x_axis(t_data *data, double x, double y, double angle)
{
	int	x_int;
	int	y_int;

	x_int = (int)x;
	y_int = (int)y;
	if ((double)180 < angle && angle < (double)360)
		y_int--;
	return (data->map[y_int][x_int]);
}

char	check_map_y_axis(t_data *data, double x, double y, double angle)
{
	int	x_int;
	int	y_int;

	x_int = (int)x;
	y_int = (int)y;
	if ((double)90 < angle && angle < 270)
		x_int--;
	return (data->map[y_int][x_int]);
}

double	set_delta_x(double angle)
{
	double	delta_x;

	delta_x = tan (angle * M_PI / (double)180);
	if (((double)90 < angle && angle < (double)180)
	|| ((double)180 < angle && angle < (double)270))
		delta_x = - delta_x;
	return (delta_x);
}

double	set_delta_y(double angle)
{
	double	delta_y;

	delta_y = (double)1 / tan (angle * M_PI / 180);
	if (((double)180 < angle && angle < (double)270)
	|| ((double)270 < angle && angle < (double)360))
		delta_y = - delta_y;
	return (delta_y);
}

t_status		set_init_data_x_axis(t_data *data, double angle)
{
	int			dx;
	int			dy;
	t_status data_init;
	double		tmp;

	dx = (int)data->pos_x;
	dy = (int)data->pos_y;
	if (((double)0 < angle && angle < (double)90)
	|| ((double)90 < angle && angle <(double)180))
		dy++;
	if (dy > data->pos_y)
		tmp = (double)dy - data->pos_y;
	else
		tmp = data->pos_y - (double)dy;
	if (((double)180 < angle && angle < (double)270)
	|| ((double)270 < angle && angle <(double)360))
		tmp = -tmp;
	data_init.init_y = (double)dy;
	data_init.init_x = data->pos_x + tmp / tan (angle * M_PI / 180);
	return (data_init);
}

t_status	set_init_data_y_axis(t_data *data, double angle)
{
	int			dx;
	int			dy;
	t_status data_init;
	double		tmp;

	dx = (int)data->pos_x;
	dy = (int)data->pos_y;
	if (((double)0 < angle && angle < (double)90)
	|| ((double)270 < angle && angle <(double)360))
		dx++;
	if ((double)dx > data->pos_x)
		tmp =(double)dx - data->pos_x;
	else
		tmp =  data->pos_x - (double)dx;
	if (((double)90 < angle && angle < (double)180)
	|| ((double)180 < angle && angle <(double)270))
		tmp = -tmp;
	data_init.init_x = (double)dx;
	data_init.init_y = data->pos_y + tmp * tan(angle * M_PI / 180);
	return (data_init);
}

int	init_check(t_status data_init, t_data *data)//マップによって異なる
{
	if (((double)0 <= data_init.init_x && data_init.init_x <= (double)data->max_x)
	&& ((double)0 <= data_init.init_y && data_init.init_y <= (double)data->max_y))
		return (0);
	else
		return (1);
}

t_status	culc_intersection_x_axis(t_data *data, double angle)
{
	t_status	data_init;
	double		delta_y;
	double		tmp_distance;

	delta_y = set_delta_y(angle);
	data_init = set_init_data_x_axis(data, angle);
	if (init_check(data_init, data) == 1)
	{
		data_init.distance = -1;
		return (data_init);
	}
	while (check_map_x_axis(data, data_init.init_x, data_init.init_y, angle) != '1')
	{
		data_init.init_x = data_init.init_x + delta_y;
		if (init_check(data_init, data) == 1)
			break ;
		if (((double)0 < angle && angle < (double)90)
		|| ((double)90 < angle && angle < (double)180))
			data_init.init_y++;
		else
			data_init.init_y--;
	}
	tmp_distance = sqrt((data_init.init_x - data->pos_x) * (data_init.init_x - data->pos_x) + (data_init.init_y - data->pos_y) * (data_init.init_y - data->pos_y));
	data_init.distance = tmp_distance * cos((data->direction - angle) * M_PI / (double)180); 
	return (data_init);
}

t_status	culc_intersection_y_axis(t_data *data, double angle)
{
	t_status	data_init;
	double		delta_x;
	double		tmp_distance;

	delta_x = set_delta_x(angle);
	data_init = set_init_data_y_axis(data, angle);
	if (init_check(data_init, data) == 1)
	{
		data_init.distance = -1;
		return (data_init);
	}
	while (check_map_y_axis(data, data_init.init_x, data_init.init_y, angle) != '1')
	{
		data_init.init_y = data_init.init_y + delta_x;
		if (init_check(data_init, data) == 1)
			break ;
		if (((double)0 < angle && angle < (double)90)
		|| ((double)270 < angle && angle < (double)360))
			data_init.init_x++;
		else
			data_init.init_x--;
	}
	tmp_distance = sqrt((data_init.init_x - data->pos_x) * (data_init.init_x - data->pos_x) + (data_init.init_y - data->pos_y) * (data_init.init_y - data->pos_y));
	data_init.distance = tmp_distance * cos((data->direction - angle) * M_PI / (double)180);
	return (data_init);
}

t_status	multiple_parallel_intersection(t_data *data, double angle)
{
	t_status	data_init;
	int			x_int;

	x_int = data->pos_x;
	data_init.init_y = data->pos_y;
	if (angle == (double) 0)
		x_int ++;
	data_init.init_x = (double)x_int;
	while (check_map_y_axis(data, data_init.init_x, data_init.init_y, angle) != '1')
	{
		if (angle == 0)
			data_init.init_x = data_init.init_x + (double)1;
		else
			data_init.init_x = data_init.init_x - (double)1;
	}
	if (angle == (double)0)
		data_init.distance = data_init.init_x - data->pos_x;
	else
		data_init.distance = data_init.init_x;
	return (data_init);
}

t_status	multiple_vertical_intersection(t_data *data, double angle)
{
	t_status	data_init;
	int			y_int;

	y_int = data->pos_y;
	data_init.init_x = data->pos_x;
	if (angle == (double) 90)
		y_int ++;
	data_init.init_y = (double)y_int;
	while (check_map_x_axis(data, data_init.init_x, data_init.init_y, angle) != '1')
	{
		if (angle == 90)
			data_init.init_y = data_init.init_y + (double)1;
		else
			data_init.init_y = data_init.init_y - (double)1;
	}
	if (angle == (double)270)
		data_init.distance = data->pos_y - data_init.init_y;
	else
		data_init.distance = data_init.init_y;
	return (data_init);
}

t_status	choice_distance(t_status x_axis, t_status y_axis, double angle)
{
	if (x_axis.distance == -1)
	{
		y_axis.dir = WEST_IMG;
		if (90 < angle && angle < 270)
			y_axis.dir = EAST_IMG;
		y_axis.pos = y_axis.init_y - (int)y_axis.init_y;
		return (y_axis);
	}
	if (y_axis.distance == -1)
	{
		x_axis.dir = SOUTH_IMG;
		if (angle < 180)
			x_axis.dir = NORTH_IMG;
		x_axis.pos = x_axis.init_x - (int)x_axis.init_x;
		return (x_axis);
	}
	if (x_axis.distance > y_axis.distance)
	{
		y_axis.dir = WEST_IMG;
		if (90 < angle && angle < 270)
			y_axis.dir = EAST_IMG;
		y_axis.pos = y_axis.init_y - (int)y_axis.init_y;
		return (y_axis);
	}
	else
	{
		x_axis.dir = SOUTH_IMG;
		if (angle < 180)
			x_axis.dir = NORTH_IMG;
		x_axis.pos = x_axis.init_x - (int)x_axis.init_x;
		return (x_axis);
	}
}

void	step_position(t_data *data, double angle, int x)
{
	t_status	intersection_x_axis;
	t_status	intersection_y_axis;
	t_status	result_data;

	if (angle == (double)0 || angle == (double)180)
	{
		intersection_y_axis = multiple_parallel_intersection(data, angle);
		result_data = intersection_y_axis;
		result_data.dir = EAST_IMG;
		if (angle == (double)0)
			result_data.dir = WEST_IMG;
		result_data.pos = result_data.init_y - (int)result_data.init_y;
	}
	else if (angle == (double)90 || angle == (double)270)
	{
		intersection_x_axis = multiple_vertical_intersection(data, angle);
		result_data = intersection_x_axis;
		result_data.dir = SOUTH_IMG;
		if (angle == ((double)90))
			result_data.dir = NORTH_IMG;
		result_data.pos = result_data.init_x - (int)result_data.init_x;
	}
	else
	{
		intersection_x_axis = culc_intersection_x_axis(data, angle);
		intersection_y_axis = culc_intersection_y_axis(data, angle);
		result_data = choice_distance(intersection_x_axis, intersection_y_axis, angle);
	}
	result_data.angle = angle;
	// printf("x ->angle %f data (%f, %f) distance %f, dir %d\n", intersection_x_axis.angle, intersection_x_axis.init_x, intersection_x_axis.init_y, intersection_x_axis.distance, intersection_x_axis.dir);
	// printf("y ->angle %f data (%f, %f) distance %f, dir %d\n", intersection_y_axis.angle, intersection_y_axis.init_x, intersection_y_axis.init_y, intersection_y_axis.distance, intersection_y_axis.dir);
	// printf("angle %f data (%f, %f) distance %f, dir %d\n", result_data.angle, result_data.init_x, result_data.init_y, result_data.distance, result_data.dir);
	result_data.height_ratio = atan(0.5 / result_data.distance) / M_PI * 180 / (double)VIEW_ANGLE_Y * (double) 2;
	result_data.height	= (int)DISPLAY_HALF * result_data.height_ratio;
	result_data.height_per_pixel = (float)result_data.height / (float)(data->xpm_height / 2);
	// printf("angle %f %f\n", angle, result_data.height_ratio);
	
	update_display(data, x, result_data);
}

void	culc_distance(t_data *data)
{
	double	shift_angle;
	double	start_angle;
	double	finish_angle;
	double	angle;
	int		x;

	x = 0;
	shift_angle = (double)VIEW_ANGLE / (double)DISPLAY_X;
	start_angle = data->direction - (double)VIEW_ANGLE / (double)2;
	finish_angle = data->direction + (double)VIEW_ANGLE / (double)2;
	while (start_angle <= finish_angle)
	{
		angle = start_angle;
		if (start_angle > 360)
			angle = start_angle - 360;
		if (start_angle < 0)
			angle = start_angle + 360;
		step_position(data, angle, x);
		start_angle += shift_angle;
		x++;
	}
	update_minimap(data);
}
