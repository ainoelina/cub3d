/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 10:11:11 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/18 12:02:30 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialise_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	map->map = malloc(sizeof(char *) * (map->x_max + 1));
	while (x < map->x_max)
	{
		map->map[x] = malloc(sizeof(char) * (map->y_max + 1));
		y = 0;
		while (y < map->y_max)
		{
			map->map[x][y] = 'A';
			y++;
		}
		map->map[x][y] = '\0';
		x++;
	}
}

void	init_text(t_all *p, char *cub, int screenshot)
{
	t_walls		wall;
	t_texture	txt;
	t_map		map;
	t_spr_ptr	*sprptr;
	t_rays		ray;

	map.map = NULL;
	map.x = 0;
	map.y = 0;
	txt.north_tex = NULL;
	txt.east_tex = NULL;
	txt.south_tex = NULL;
	txt.west_tex = NULL;
	txt.spr_tex = NULL;
	txt.floor = -1;
	txt.ceiling = -1;
	sprptr = NULL;
	p->no_resizing = 0;
	p->walls = &wall;
	p->txt = &txt;
	p->map = &map;
	p->ray = &ray;
	p->spr = sprptr;
	start_game(p, cub, screenshot);
}

void	init_all(char *cub, int screenshot)
{
	t_all		p;
	t_mlx		mlx;
	t_player	pl;
	t_movement	move;

	mlx.mlx_ptr = NULL;
	mlx.win_ptr = NULL;
	mlx.img_ptr = NULL;
	mlx.img_addr = NULL;
	mlx.screenh = 0;
	mlx.screenw = 0;
	mlx.resolution = 0;
	pl.x = 0;
	pl.y = 0;
	pl.x_dir = 0;
	pl.y_dir = 0;
	pl.pos_check = 0;
	p.lines = NULL;
	p.mlx = &mlx;
	p.pl = &pl;
	p.move = &move;
	init_text(&p, cub, screenshot);
}
