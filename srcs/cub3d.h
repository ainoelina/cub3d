/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 10:38:56 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/05 14:58:25 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ~~~~~~~~~ LIBRARIES ~~~~
*/
# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

/*
** ~~~~~~~~~ KEYS ~~~~
*/
# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125 

/*
** ~~~~~~~~~ COLOURS ~~~~
*/
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF

/*
** ~~~~~~~~~ DIMENSIONS ~~~~
*/
# define W_WIDTH 640
# define W_HEIGTH 480

/*
** ~~~~~~~~~ GNL ~~~~
*/

# define BUFFER_SIZE 4096

/*
** ~~~~~~~~~ ERRORS ~~~~
*/
# define FD -1
# define COLOR_INPUT -2
# define RGB_STRING -3
# define TXT_DOUBLE -4
# define TXT_INPUT -5
# define XPM_MALLOC -6
# define MAP_MALLOC -7
# define MAP_INVALID -8
# define RES_DOUBLE -9
# define RES_INVALID -10
# define COLOR_DOUBLE -11
# define MISSING_INPUT -12
# define MAP_WALLS -13
# define PLAYER_NF -14
# define PLAYER_DOUBLE -15
# define SPRITE_MALLOC -16
# define BUF_MALLOC -17
# define MLX_FAIL -18

/*
** ~~~~~~~~~ STRUCTS ~~~~
*/

typedef struct s_mlx
{
	void	*ptr;
}				t_mlx;

typedef struct s_img
{
	void	*ptr;
	int		*addr;
	int		s_len;
	int		bpp;
	int		endian;
}				t_img;

typedef struct s_map
{
	double	time;
	double	time_old;
	int		x;
	int		y;
	int		x_old;
	int		y_old;
}				t_map;

typedef struct s_win
{
	void	*ptr;
	int		width;
	int		heigth;
	int		res_check;
}				t_win;

typedef struct s_pos
{
	int		x;
	int		y;
}				t_pos;

typedef struct s_text
{
	int					*data;
	int					sizeline;
	int					heigth;
	unsigned int		floor;
	unsigned int		ceiling;
	char				*n_txt;
	char				*e_txt;
	char				*s_txt;
	char				*w_txt;
	char				*sp_txt;
	int					*north;
	int					*east;
	int					*south;
	int					*west;
	int					*spr;
	void				*no;
	void				*ea;
	void				*so;
	void				*we;
	void				*sp;
	int					n_sl;
	int					n_h;
	int					e_sl;
	int					e_h;
	int					s_sl;
	int					s_h;
	int					w_sl;
	int					w_h;
	int					sp_sl;
	int					sp_w;
	int					sp_h;
}				t_text;

typedef struct s_world
{
	int		max_col;
	int		max_row;
	int		col;
	int		row;
	char	**map;
}				t_world;

typedef struct s_pl
{
	double	x_pos;
	double	y_pos;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
	double	camera;
	char	forw;
	char	back;
	char	l;
	char	r;
	char	l_rot;
	char	r_rot;
	char	pos;
}				t_pl;

typedef struct s_walls
{
	char	dir;
	int		heigth;
	int		start;
	int		end;

}				t_walls;

typedef struct s_draw_sprites
{
	double	x_spr;
	double	y_spr;
	double	x_mod;
	double	y_mod;
	double	inverse;
	int		screen;
	int		width;
	int		heigth;
	int		x_start;
	int		x_end;
	int		y_start;
	int		y_end;
	int		x_text;
	int		y_text;
	int		x;
	int		y;
	int		d;

}				t_draw_sprites;

typedef struct s_spr
{
	float	x;
	float	y;
}				t_spr;

typedef struct s_sprites
{
	t_spr	*spr;
	int		num;
	int		*order;
}				t_sprites;

typedef struct s_rays
{
	double	x_dir;
	double	y_dir;
	double	x_delta;
	double	y_delta;
	double	x_side;
	double	y_side;
	double	perp_wall;
	double	buf[4000];
	double	spritedist;
	double	w;
	int		x_step;
	int		y_step;
	int		x_map;
	int		y_map;
	int		hit;
	int		side;
}				t_rays;

typedef struct s_param
{
	t_mlx		mlx;
	t_img		img;
	t_win		win;
	t_text		text;
	t_map		map;
	t_pos		pos;
	t_world		world;
	t_pl		pl;
	t_sprites	sprites;
	t_rays		rays;
	t_walls		walls;
	t_spr		*spr;
	t_spr		*spr_sorted;
	char		**lines;
	int			*sp_order;
	int			sp_num;
	int			err;
	int			ray;
	int			txt;
}				t_param;

/*
** 2D map & printing
*/

/*
** texture & xpm
*/
void	handle_textures(t_param *p);
void	my_mlx_pixel_put(t_param *p, int x, int y, unsigned int color);

/*
** ~~~~~~~~~ BASIC FUNCTIONS ~~~~
*/

void	init_param(char *file);
void	start_point(t_param p, char *file);

/*
** ~~~~~~~~~ ERRORS & CLOSING GAME ~~~~
*/
int		close_game(t_param *p);

void	error_handling(int error, t_param *p);

/*
** ~~~~~~~~~ CHECKER FUNCTIONS ~~~~
*/

int		key(int key, t_param *p);
int		cub_check(char *cub);

void	check_input(t_param *p);
void	check_map(t_param *p, int x, int y);

/*
** ~~~~~~~~~ PARSING FUNCTIONS ~~~~
*/
void	sprites(t_param *p);
int		parsing(t_param *p, char *file);
int		parser(t_param *p, char *file);

//oid	parse_map1(t_param *p, char *line, int *i);
void	parse_map(t_param *p, char **array);
void	get_resolution(t_param *p, char *line, int *i);
void	set_texture(t_param *p, char *line, char **texture, int *i);
void	set_color(t_param *p, char *line, unsigned int *color, int *i);

void	define_position(t_param *p);

t_spr	*parse_sprites(t_param *p);

void	fill(t_param *p);
void	setup_walls(t_param *p);
void	texture(t_param *p);
void	raycast(t_param *p);
void	ceiling_floor(t_param *p);
void	choose_texture(t_param *p);
void	draw_line(t_param *p);

/*
** ~~~~~~~~~ UTIL FUNCTIONS ~~~~
*/
int		my_atoi(char *line, int *i);

void	skip_spaces(int *i, char *line);
void	copier(char **lines, int *j, char **temp);


/*
** ~~~~~~~~~ GNL FUNCTIONS ~~~~
*/

int		get_next_line(int fd, char **line);
int		minus_return(char *buffer);
char	*null_return(char *string);
char	*join_strings(char *rest, char *buffer);
size_t	str_len(char *str);

#endif
