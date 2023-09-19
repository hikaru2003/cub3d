/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:45:21 by hikaru            #+#    #+#             */
/*   Updated: 2023/09/19 17:49:10 by hikaru           ###   ########.fr       */
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

# define KEY_ESC		65307

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define DISPLAY_X		1000
# define DISPLAY_Y		600

# define NORTH			270
# define SOUTH			90
# define WEST			180
# define EAST			0

# define VIEW_ANGLE		120
# define STEP			0.2

# define ANGLE			30

# define ESC			53
# define UP_ARROW		126
# define DOWN_ARROW		125
# define RIGHT_ARROW	124
# define LEFT_ARROW		123

#define KEY_W			13
#define KEY_A			0
#define KEY_S			1
#define KEY_D			2


typedef	struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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



// check_file.c
void	check_file(char *filename, t_data *data);

// check_map.c
void	check_map(t_data *data);

// create_map.c
void	create_map(t_data *data, char *filename);

// destroy.c
int		ft_destroy(t_data *data);

// draw.c
int		draw_map(t_data *data);

// error.c
void	print_error(char *msg);

// libft
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);


// gnl
char	*get_next_line(int fd);
char	*ft_free(char **str);
char	*ft_strjoin(char *line, char *buf);


// init_data.c
t_data	*init_data(void);

// next_frame.c
void	reset_display(t_data *data);
void	update_display(t_data *data, int index);
int		next_frame(int keycode, t_data *data);


#endif