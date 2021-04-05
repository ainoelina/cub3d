/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 10:45:09 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/30 15:10:55 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** possibility to leave out space skipping
** subject says spaces are valid part of the map and up for
** me to handle --> should not show up for the player
*/

/*
** for create_map, the norminette issue could be fixed
** with ignoring the spaces but maybe something to look more
** closely later on to see how the spaces should be handled
*/

void	create_map(char **array, t_param *p)
{
	int	i;
	int	j;
	int	y;
	int	x;

	i = 0;
	x = 0;
	while (array[i])
	{
		j = 0;
		y = 0;
		while (array[i][j])
		{
			while (array[i][j] == ' ')
				j++;
			if (array[i][j])
			{
				p->world.map[x][y] = array[i][j];
				j++;
				y++;
			}
		}
		printf("map line now is %s\n", p->world.map[x]);
		j = 0;
		x++;
		i++;
	}
}

int	count_col(t_param *p, char **array)
{
	int	col_counter;
	int	y;
	int	empty;

	empty = 0;
	col_counter = 0;
	while (array[col_counter])
	{
		y = 0;
		while (array[col_counter][y] == ' ')
			y++;
		if (!array[col_counter][y])
			empty = 1;
		if (empty && array[col_counter][y])
			error_handling(MAP_INVALID, p);
		col_counter++;
	}
	return (col_counter);
}

int	count_row(char **array)
{
	int	x;
	int	y;
	int	row_counter;
	int	rows;

	x = 0;
	y = 0;
	row_counter = 0;
	while (array[x])
	{
		y = 0;
		rows = 0;
		while (array[x][y])
		{
			if (array[x][y] != ' ')
				rows++;
			y++;
		}
		if (rows > row_counter)
			row_counter = rows;
		x++;
	}
	return (row_counter);
}

void	map_init(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	p->world.map = malloc(sizeof(int *) * (p->world.max_row + 1));
	while (i < p->world.max_row)
	{
		p->world.map[i] = malloc(sizeof(int) * (p->world.max_col + 1));
		j = 0;
		while (j < p->world.max_col)
		{
			p->world.map[i][j] = 'A';
			j++;
			if (j == p->world.max_col)
				p->world.map[i][j] = '\0';
		}
		i++;
	}
}

void	parse_map(t_param *p, char **map_array)
{
	p->world.max_row = count_col(p, map_array);
	p->world.max_col = count_row(map_array);
	printf("max row is %i\n", p->world.max_row);
	printf("max col is %i\n", p->world.max_col);
	map_init(p);
	create_map(map_array, p);
	printf("print max col %i, max row %i\n", p->world.max_col, p->world.max_row);
	define_position(p);
	printf("player position now is x = %f y = %f\n", p->pl.x_pos, p->pl.y_pos);
//	check_map(p, p->pl.x_pos, p->pl.y_pos);
}
