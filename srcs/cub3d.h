/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 17:07:35 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/05 11:36:49 by avuorio       ########   odam.nl         */
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
** ~~~~~~~~~ SPEED ~~~~
*/
# define SPEED 0.2
# define TURN 0.02

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
** ~~~~~~~~~ ERROR NUMBERS ~~~~
*/

# define MLX_FUNCTION -1
# define FD -2
# define MALLOC_FAIL -3
# define NO_MAP -4
# define TEXTURE_DOUBLE -5
# define RESOLUTION_DOUBLE -6
# define RESOLUTION_INVALID -7
# define COLOUR_DOUBLE -8
# define COLOUR_INPUT -9
# define ADDITIONAL_INPUT -10
# define PLAYER_DOUBLE -11
# define PLAYER_NF -12
# define MAP_INVALID -13

/*
** ~~~~~~~~~ DIRECTIONS ~~~~
*/
# define NORTH 9
# define EAST 8
# define SOUTH 7
# define WEST 6
# define SPRITE 5

# define BUFFER_SIZE 4096

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*img_ptr;
	void	*win_ptr;
	int		*img_addr;
	int		bpp;
	int		sizeline;
	int		endian;
	int		screenw;
	int		screenh;
	int		resolution;
}	t_mlx;

typedef struct s_texture
{
	unsigned int	floor;
	unsigned int	ceiling;
	char			*north_tex;
	char			*east_tex;
	char			*south_tex;
	char			*west_tex;
	char			*spr_tex;
	void			*northptr;
	void			*eastptr;
	void			*southptr;
	void			*westptr;
	void			*sprptr;
	int				*north;
	int				*east;
	int				*south;
	int				*west;
	int				*sprite;
	int				*data;
	int				sl;
	int				heigth;
	int				north_sl;
	int				north_h;
	int				east_sl;
	int				east_h;
	int				south_sl;
	int				south_h;
	int				west_sl;
	int				west_h;
	int				spr_sl;
	int				spr_h;
	int				spr_w;
	int				num;
}	t_texture;

typedef struct s_map
{
	char	**map;
	int		x_max;
	int		y_max;
	int		x;
	int		y;

}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
	double	camera;
	int		pos_check;
}	t_player;

typedef struct s_movement
{
	int	forw;
	int	backw;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
}	t_movement;

typedef struct s_walls
{
	char	direction;
	int		heigth;
	int		start;
	int		end;
	int		*text;
	int		sl;
	int		line_h;
	int		texture;
}	t_walls;

typedef struct s_rays
{
	double	buf[4000];
	double	x_dir;
	double	y_dir;
	double	x_delta;
	double	y_delta;
	double	x_side;
	double	y_side;
	double	wall_dist;
	double	wall_hit;
	double	wall;
	int		x_map;
	int		y_map;
	int		x_step;
	int		y_step;
	int		hit;
	int		side;
}	t_rays;

typedef struct s_drawsprite
{
	double	x_sprite;
	double	y_sprite;
	double	x_transf;
	double	y_transf;
	double	invdet;
	int		scr;
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
}	t_drawsprite;

typedef struct s_spr_ptr
{
	double	x;
	double	y;
}	t_spr_ptr;

typedef struct s_all
{
	t_mlx		*mlx;
	t_texture	*txt;
	t_map		*map;
	t_player	*pl;
	t_movement	*move;
	t_walls		*walls;
	t_spr_ptr	*spr;
	t_spr_ptr	*spr_sorted;
	t_rays		*ray;
	char		**lines;
	int			*spriteorder;
	int			spritenum;
	int			stripe;
	int			screenshot;
	int			no_resizing;

}	t_all;

/*
** ~~~~~~~~~ BMP SCREENSHOT ~~~~
*/

void		create_bmp(t_all *p);

/*
** ~~~~~~~~~ GAME ACTIONS ~~~~
*/

int			key_pressed(int key, t_all *p);
int			key_released(int key, t_all *p);
int			close_game(t_all *p);
int			move(t_all *p);
int			run_game(t_all *p);


void		start_game(t_all *p, char *cub, int screenshot);
void		make_screenshot(t_all *p);

/*
** ~~~~~~~~~ INIT FUNCTIONS ~~~~
*/
void		init_all(char *cub, int screenshot);
void		initialise_map(t_map *map);
void		init_screen(t_mlx *mlx);
void		handle_texture(t_all *p, t_texture *txt);


/*
** ~~~~~~~~~ CHECK FUNCTIONS ~~~~
*/

int			save_check(char *argv, char *save);
int			file_check(char *file, char format);
int			check_map(t_all *p);

void		error_handling(int error, t_all *p);
void		map_check(t_all *p, t_map *m, char **map);
void	checkmap(t_all *p, int x, int y);

/*
** ~~~~~~~~~ UTILS ~~~~
*/
void		skip_spaces(int *i, char *line);
void		copy_lines(char **lines, int *index, char **save);
void		free_lines(t_all *p);

int			my_atoi(char *line, int *i);
int			is_space(char c);

/*
** ~~~~~~~~~ GET_NEXT_LINE ~~~~
*/
size_t		str_len(char *str);

char		*null_return(char *string);
char		*join_strings(char *rest, char *buffer);

int			minus_return(char *buffer);
int			get_next_line(int fd, char **line);

/*
** ~~~~~~~~~ PARSING ~~~~
*/
void		parser(t_all *p, char *cub);
void		parse_map(t_all *p, char **array);
void		parse_position(t_all *p);
void		set_texture(t_all *p, char *line, char **texture, int *i);
void		set_resolution(t_all *p, char *line, int *i);
void		set_colour(t_all *p, char *line, unsigned int *colour, int *i);

t_spr_ptr	*parse_sprites(t_all *p, int i, int j);

/*
** ~~~~~~~~~ RAYCASTING ~~~~
*/

void		draw(t_all *p, t_walls *walls, int start, int end);
void		texturise(t_rays *ray, t_walls *walls);
void		raycast(t_all *p);
void		define_walls(t_walls *walls, t_all *p);
void		define_texture(t_texture *txt, t_walls *walls);
void		floor_ceiling(t_all *p);
void		draw_stripe(t_walls *walls, t_mlx *mlx, t_all *p, int stripe);
void		handle_sprites(t_all *p, t_player *pl, t_mlx *mlx);
void		draw_sprites(t_drawsprite *spr, t_mlx *mlx, t_all *p);

#endif