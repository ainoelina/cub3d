/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 13:43:09 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/13 11:31:14 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_possible(char c)
{
	if (c == '1' || c == '2')
		return (0);
	return (1);
}

void	rotate(t_player *pl, double d)
{
	double	olddir;
	double	oldplane;

	olddir = pl->x_dir;
	oldplane = pl->x_plane;
	pl->x_dir = (pl->x_dir * cos(d * TURN) - pl->y_dir * sin(d * TURN));
	pl->y_dir = (olddir * sin(d * TURN) + pl->y_dir * cos(d * TURN));
	pl->x_plane = (pl->x_plane * cos(d * TURN) - pl->y_plane * sin(d * TURN));
	pl->y_plane = (oldplane * sin(d * TURN) + pl->y_plane * cos(TURN));
}

void	leftright(t_movement *move, t_player *pl, t_map *map)
{
	if (move->left)
	{
		if (move_possible(map->map[(int)(pl->x)]
			[(int)(pl->y + pl->x_dir * SPEED)]))
			pl->y = pl->y + pl->x_dir * SPEED * 0.5;
		if (move_possible(map->map[(int)(pl->x - pl->y_dir * SPEED)]
			[(int)(pl->y)]))
			pl->x = pl->x - pl->y_dir * SPEED * 0.5;
	}
	if (move->right)
	{
		if (move_possible(map->map[(int)(pl->x)]
			[(int)(pl->y - pl->x_dir * SPEED)]))
			pl->y = pl->y - pl->x_dir * SPEED * 0.5;
		if (move_possible(map->map[(int)(pl->x + pl->y_dir * SPEED)]
			[(int)(pl->y)]))
			pl->x = pl->x + pl->y_dir * SPEED * 0.5;
	}
}

void	forwardbackward(t_movement *move, t_player *pl, t_map *map)
{
	if (move->forw)
	{
		if (move_possible(map->map[(int)(pl->x + pl->x_dir * SPEED)]
			[(int)(pl->y)]))
			pl->x = pl->x + pl->x_dir * SPEED * 0.5;
		if (move_possible(map->map[(int)(pl->x)][(int)(pl->y
			+ pl->y_dir * SPEED)]))
			pl->y = pl->y + pl->y_dir * SPEED * 0.5;
	}
	if (move->backw)
	{
		if (move_possible(map->map[(int)(pl->x - pl->x_dir * SPEED)]
			[(int)(pl->y)]))
			pl->x = pl->x - pl->x_dir * SPEED * 0.5;
		if (move_possible(map->map[(int)(pl->x)][(int)(pl->y
			- pl->y_dir * SPEED)]))
			pl->y = pl->y - pl->y_dir * SPEED * 0.5;
	}
}

int	move(t_all *p)
{
	forwardbackward(p->move, p->pl, p->map);
	leftright(p->move, p->pl, p->map);
	if (p->move->rotate_right)
		rotate(p->pl, -1);
	if (p->move->rotate_left)
		rotate(p->pl, 1);
	return (0);
}
