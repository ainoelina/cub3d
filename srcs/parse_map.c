/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 11:00:04 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/20 12:17:25 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// remove the '\0'addition if doesn't start working 

void	create_map(t_map *map, char **array, int i, int j)
{
	int	last;

	last = 0;
	while (array[i])
	{
		map->y = 0;
		while (array[i][j])
		{
			if (array[i][j])
			{
				map->map[map->x][map->y] = array[i][j];
				map->y++;
				j++;
			}
			if (last < map->y)
				last = map->y;
		}
		map->map[map->x][map->y] = '\0';
		printf("%2i-map: %s\n", (i + 1), map->map[map->x]);
		j = 0;
		map->x++;
		i++;
	}
	map->y_max = last;
}

int	count_ymax(char **array)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (array[x])
	{
		y = 0;
		while (array[x][y])
			y++;
		if (count < y)
			count = y;
		x++;
	}
	return (count);
}

int	count_xmax(t_all *p, char **array)
{
	int	x;
	int	y;
	int	empty;

	x = 0;
	empty = 0;
	while (array[x])
	{
		y = 0;
		while (array[x][y] == ' ')
			y++;
		if (!array[x][y])
			empty = 1;
		if (array[x][y] && empty)
			error_handling(ADDITIONAL_INPUT, p);
		x++;
	}
	return (x);
}

void	parse_map(t_all *p, char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	p->map->x = 0;
	p->map->y = 0;
	p->map->x_max = count_xmax(p, array);
	p->map->y_max = count_ymax(array);
	initialise_map(p->map);
	create_map(p->map, array, i, j);
	parse_position(p);
	check_map(p->map, p);
}
