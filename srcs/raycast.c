/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 10:10:40 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/02 09:22:39 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** fabs function computes the absolute value of 
** floating point number x
*/

void	rays(t_param *p)
{
	p->pl.camera = 2 * p->ray / (double)p->win.width - 1;
	p->rays.x_dir = p->pl.x_dir + p->pl.x_plane * p->pl.camera;
	p->rays.y_dir = p->pl.y_dir + p->pl.y_plane * p->pl.camera;
	p->rays.x_map = (int)(p->pl.x_pos);
	p->rays.y_map = (int)(p->pl.y_pos);
	p->rays.x_delta = fabs(1 / p->rays.x_dir);
	p->rays.y_delta = fabs(1 / p->rays.y_dir);
	p->rays.hit = 0;
}

void	steps(t_param *p)
{
	if (p->rays.x_dir < 0)
	{
		p->rays.x_step = -1;
		p->rays.x_side = (p->pl.x_pos - p->rays.x_map) * p->rays.x_delta;
	}
	else
	{
		p->rays.x_step = 1;
		p->rays.x_side = (p->rays.x_map + 1.0 - p->pl.x_pos) * p->rays.x_delta;
	}
	if (p->rays.y_dir < 0)
	{
		p->rays.y_step = -1;
		p->rays.y_side = (p->pl.y_pos - p->rays.y_map) * p->rays.y_delta;
	}
	else
	{
		p->rays.y_step = 1;
		p->rays.y_side = (p->rays.y_map + 1.0 - p->pl.y_pos) * p->rays.y_delta;
	}
}

void	hits(t_param *p)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (p->rays.x_side < p->rays.y_side)
		{
			p->rays.x_side += p->rays.x_delta;
			p->rays.x_map += p->rays.x_step;
			p->rays.side = 0;
		}
		else
		{
			p->rays.y_side += p->rays.y_delta;
			p->rays.y_map += p->rays.y_step;
			p->rays.side = 1;
		}
		if (p->world.map[p->rays.x_map][p->rays.y_map] == '1')
			hit = 1;
	}
}

/*
** based on the side of rays, the wall direction is set
*/

void	walls(t_param *p)
{
	if (p->rays.side == 0)
	{
		if (p->rays.x_map < p->pl.x_pos)
			p->walls.dir = 'N';
		else
			p->walls.dir = 'S';
		p->rays.perp_wall = (p->rays.x_map - p->pl.x_pos
				+ (1 - p->rays.x_step) / 2) / p->rays.x_dir;
		p->rays.w = p->pl.y_pos + p->rays.perp_wall * p->rays.y_dir;
	}
	else
	{
		if (p->rays.y_map < p->pl.y_pos)
			p->walls.dir = 'W';
		else
			p->walls.dir = 'E';
		p->rays.perp_wall = (p->rays.y_map - p->pl.y_pos
				+ (1 - p->rays.y_step) / 2) / p->rays.y_dir;
		p->rays.w = p->pl.x_pos + p->rays.perp_wall * p->rays.x_dir;
	}
	p->rays.buf[p->ray] = p->rays.perp_wall;
}

void	raycast(t_param *p)
{
	p->ray = 0;
	p->rays.buf = malloc(sizeof(double) * p->win.width + 1);
	if (!p->rays.buf)
		error_handling(BUF_MALLOC, p);
	while (p->ray < p->win.width)
	{
		rays(p);
		steps(p);
		hits(p);
		walls(p);
		setup_walls(p);
		choose_texture(p);
		texture(p);
		draw_line(p);
		p->ray++;
	}
	sprites(p);
	free(p->rays.buf);
}
