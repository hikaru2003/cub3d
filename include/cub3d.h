/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:45:21 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/27 19:14:54 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <libc.h>
# include <mlx.h>
# include <math.h>
#include <stdio.h>
#include <time.h>
# include "../libft/libft.h"

# define KEY_ESC		65307

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define DISPLAY_X		1000
# define DISPLAY_Y		600
# define MIN_WALL_HEIGHT	500
# define MAX_WALL_HEIGHT	700

# define MINIMAP_PIXEL	10

# define NORTH			270
# define SOUTH			90
# define WEST			180
# define EAST			0

# define NORTH_IMG		0
# define SOUTH_IMG		1
# define WEST_IMG		2
# define EAST_IMG		3


# define VIEW_ANGLE		60
# define VIEW_ANGLE_Y	40
# define STEP			0.1

# define ANGLE			1

# define ESC			53
# define UP_ARROW		126
# define DOWN_ARROW		125
# define RIGHT_ARROW	124
# define LEFT_ARROW		123

#define KEY_W			13
#define KEY_A			0
#define KEY_S			1
#define KEY_D			2

typedef struct s_data
{
	char	**map;
	int		display[DISPLAY_Y][DISPLAY_X];
	double	direction;
	double	pos_x;
	double	pos_y;
	int		max_x;
	int		max_y;
	char	**path;
	void	*img;
	int		xpm_width;
	int		xpm_height;
	void	*direction_img[4];
	void	*north_img;
	void	*south_img;
	void	*west_img;
	void	*east_img;
	int		floor_rgb;
	int		ceiling_rgb;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

typedef struct s_status
{
	double	init_x;
	double	init_y;
	double	distance;
	int		dir;
	double	pos;
	double	angle;
	double	height_ratio;
} t_status;

typedef struct s_coor
{
	int	x;
	int	y;
} t_coor;



// check_file.c
void	check_file(char *filename, t_data *data);

// check_map.c
void	check_map(t_data *data);

// create_map.c
void	create_map(char *filename, t_data *data);

// culc_distance.c
void	culc_distance(t_data *data);

// destroy.c
void	free_map(t_data *data);
void	free_path(t_data *data);
int		ft_destroy(t_data *data);

// draw.c
int		draw_map(t_data *data);

// error.c
void	print_error(char *msg);

// gnl
char	*get_next_line(int fd);
char	*gnl_strjoin(char *line, char *buf);
char	*ft_free(char **str);

// init_data.c
t_data	*init_data(void);

// next_frame.c
void	reset_display(t_data *data);
void	update_display(t_data *data, int index, t_status status);
int		next_frame(int keycode, t_data *data);


#endif