/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   position.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 11:36:15 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/05 11:33:06 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	east_west(char c, t_param *p)
{
	if (c == 'W')
	{
		p->pl.x_dir = 0;
		p->pl.y_dir = -1;
		p->pl.x_plane = -0.66;
		p->pl.y_plane = 0;
	}
	else if (c == 'E')
	{
		p->pl.x_dir = 0;
		p->pl.y_dir = 1;
		p->pl.x_plane = 0.66;
		p->pl.y_plane = 0;
	}
}

void	north_south(char c, t_param *p)
{
	if (c == 'N')
	{
		p->pl.x_dir = -1;
		p->pl.y_dir = 0;
		p->pl.x_plane = 0;
		p->pl.y_plane = 0.66;
	}
	else if (c == 'S')
	{
		p->pl.x_dir = 1;
		p->pl.y_dir = 0;
		p->pl.x_plane = 0;
		p->pl.y_plane = -0.66;
	}
}

void	init_player(char c, int x, int y, t_param *p)
{
	if (c != 'N' && c != 'E' && c != 'S' && c != 'W')
		error_handling(MAP_INVALID, p);
	if (p->pl.pos > 0)
		error_handling(PLAYER_DOUBLE, p);
	p->pl.x_pos = x + 0.5;
	p->pl.y_pos = y + 0.5;
	if (c == 'N' || c == 'S')
		north_south(c, p);
	else if (c == 'W' || c == 'E')
		east_west(c, p);
	p->pl.forw = 0;
	p->pl.back = 0;
	p->pl.l = 0;
	p->pl.r = 0;
	p->pl.r_rot = 0;
	p->pl.l_rot = 0;
	printf("player x_dir is %f\n", p->pl.x_dir);
	printf("player y_dir is %f\n", p->pl.y_dir);
	printf("player x_plane is %f\n", p->pl.x_plane);
	printf("player y_plane is %f\n", p->pl.y_plane);
}

int	check_char(char	c, int x, int y, t_param *p)
{
	if (c != '1' && c != '2' && c != '0' && c != 'A')
	{
		init_player(c, x, y, p);
		return (1);
	}
	return (0);
}

/*
** changed the loops from i <= and j <= to <
** see that if you run into problems later on
*/

void	define_position(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	p->pl.pos = 0;
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			p->pl.pos = p->pl.pos + check_char(p->world.map[i][j], i, j, p);
			j++;
		}
		i++;
	}
	if (p->pl.pos == 0)
		error_handling(PLAYER_NF, p);
}
