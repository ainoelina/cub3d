/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_position.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 12:03:54 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/05 13:01:08 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	east_west(char c, t_player *pl)
{
	if (c == 'W')
	{
		pl->x_dir = 0;
		pl->y_dir = -1;
		pl->x_plane = -0.66;
		pl->y_plane = 0;
	}
	if (c == 'E')
	{
		pl->x_dir = 0;
		pl->y_dir = 1;
		pl->x_plane = 0.66;
		pl->y_plane = 0;
	}
}

void	north_south(char c, t_player *pl)
{
	if (c == 'N')
	{
		pl->x_dir = -1;
		pl->y_dir = 0;
		pl->x_plane = 0;
		pl->y_plane = 0.66;
	}
	if (c == 'S')
	{
		pl->x_dir = 1;
		pl->y_dir = 0;
		pl->x_plane = 0;
		pl->y_plane = -0.66;
	}
}

/*
** adding 0.5 to place the player at the centre of the grid square
*/

void	init_player(char c, int x, int y, t_all *p)
{
	if (c != 'N' && c != 'E' && c != 'S' && c != 'W' && c != ' ')
		error_handling(MAP_INVALID, p);
	if (p->pl->pos_check > 0)
		error_handling(PLAYER_DOUBLE, p);
	p->pl->x = x + 0.5;
	p->pl->y = y + 0.5;
	if (c == 'N' || c == 'S')
		north_south(c, p->pl);
	if (c == 'E' || c == 'W')
		east_west(c, p->pl);
	p->move->backw = 0;
	p->move->forw = 0;
	p->move->left = 0;
	p->move->right = 0;
	p->move->rotate_left = 0;
	p->move->rotate_right = 0;
}

int	check_char(char c, int x, int y, t_all *p)
{
	if (c != '1' && c != '2' && c != '0' && c != 'A' && c != ' ')
	{
		init_player(c, x, y, p);
		return (1);
	}
	return (0);
}

void	parse_position(t_all *p)
{
	int	i;
	int	j;

	i = 0;
	p->pl->pos_check = 0;
	while (i < p->map->x_max)
	{
		j = 0;
		while (j < p->map->y_max)
		{
			p->pl->pos_check += check_char(p->map->map[i][j], i, j, p);
			j++;
		}
		i++;
	}
	if (p->pl->pos_check == 0)
		error_handling(PLAYER_NF, p);
}
