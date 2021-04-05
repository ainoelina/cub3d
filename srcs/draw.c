/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 12:45:13 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/31 12:26:53 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** ceiling_floor sets the image data for ceiling and floor by
** splitting the screen in half, filling top half with ceiling color
** and bottom half with floor color.
*/

void	ceiling_floor(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->win.width)
	{
		j = 0;
		while (j < p->win.heigth / 2)
		{
			p->text.data[j * p->win.width + i] = p->text.ceiling;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < p->win.width)
	{
		j = p->win.heigth / 2;
		while (j < p->win.heigth)
		{
			p->text.data[j * p->win.width + i] = p->text.floor;
			j++;
		}
		i++;
	}
}

// void	choose_texture(t_param *p)
// {
// 	if (p->walls.dir == 'N')
// }

/*
** draw line function 
*/

void	draw_line(t_param *p)
{
	int		i;
	int		*text;
	double	step;
	double	pos;

	i = 0;
	step = 1.0 * p->text.heigth / p->walls.heigth;
	pos = (p->walls.start - p->win.heigth / 2 + p->walls.heigth / 2) * step;
	text = p->text.data;
	while (i < p->walls.start)
	{
		*(p->img.addr + p->ray + i * p->img.s_len / 4) = p->text.ceiling;
		i++;
	}
	while (i <= p->walls.end)
	{
		*(p->img.addr + p->ray + i++ * p->img.s_len / 4) = *(text + p->txt
				+ (int)pos * p->text.sizeline / 4);
		pos = pos + step;
	}
	while (i < p->win.heigth)
		*(p->img.addr + p->ray + i++ * p->img.s_len / 4) = p->text.floor;
}

void	texture(t_param *p)
{
	p->rays.w -= floor(p->rays.w);
	p->txt = p->rays.w * (p->text.sizeline / 4);
	if (p->rays.side == 0 && p->rays.x_dir > 0)
		p->txt = (p->text.sizeline / 4) - p->txt - 1;
	else if (p->rays.side == 1 && p->rays.y_dir < 0)
		p->txt = (p->text.sizeline / 4) - p->txt - 1;
	// int num;
	// num = p->world.map[p->rays.x_map][p->rays.y_map] - 1;
	// p->rays.w -= floor(p->rays.w);
	// choose_texture(p);
	// p->txt = p->rays.w * (256 / 4);
	// if (p->rays.side == 0 && p->rays.x_dir > 0)
	// 	p->txt = (256 / 4) - p->txt - 1;
	// else if (p->rays.side == 1 && p->rays.y_dir < 0)
	// 	p->txt = (256 / 4) - p->txt - 1;
}

void	setup_walls(t_param *p)
{
	p->walls.heigth = (int)(p->win.heigth / p->rays.perp_wall);
	p->walls.start = -p->walls.heigth / 2 + p->win.heigth / 2;
	if (p->walls.start < 0)
		p->walls.start = 0;
	p->walls.end = p->walls.heigth / 2 + p->win.heigth / 2;
	if (p->walls.end >= p->win.heigth)
		p->walls.end = p->win.heigth - 1;
}
