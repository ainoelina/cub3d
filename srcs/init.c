/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:52:41 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/29 10:05:02 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_text *text)
{
	// text->n = NULL;
	// text->s = NULL;
	// text->e = NULL;
	// text->w = NULL;
	text->n_txt = NULL;
	text->e_txt = NULL;
	text->s_txt = NULL;
	text->w_txt = NULL;
	text->sp_txt = NULL;
	text->floor = 0;
	text->ceiling = 0;
}

void	init_map(t_map *map)
{
	map->y = 0;
	map-> x = 0;
	map->sprite = 0;
	map->map = NULL;
}

void	init_param(char *file)
{
	t_param		p;
	t_mlx		mlx;
	t_img		img;
	t_win		win;
	t_text		text;
	t_map		map;
	t_sprites	sprite;

	p.err = 0;
	mlx.ptr = NULL;
	img.ptr = NULL;
	img.addr = NULL;
	win.ptr = NULL;
	win.width = 0;
	win.heigth = 0;
	win.res_check = 0;
	sprite.spr = NULL;
	init_map(&map);
	init_textures(&text);
	p.sprites = sprite;
	p.map = map;
	p.mlx = mlx;
	p.img = img;
	p.win = win;
	p.text = text;
	start_point(p, file);
}
