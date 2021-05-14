/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 09:26:49 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/14 11:08:58 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char	*ft_strchr(char *str, char c)
// {
// 	while (*str)
// 	{
// 		if (*str == c)
// 			return (str);
// 		str++;
// 	}
// 	if (*str == c)
// 		return (str);
// 	return (0);
// }

// void	check_walls(t_map *map, t_all *p)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map->x_max)
// 	{
// 		if (map->map[i][j] != '1' || map->map[i + (map->x_max * map->y_max)
// 				- map->x_max] != '1')
// 			error_handling(MAP_WALLS, p);
// 		i++;
// 	}
// 	j = 0;
// 	while (j < map->y_max)
// 	{
// 		if (map->map[(j * map->x_max)] != '1' || map->map[(map->x_max
// 					+ j * map->x_max) - 1] != '1')
// 			error_handling(MAP_WALLS, p);
// 		j++;
// 	}
// }

void	checkermap(t_map *m, t_all *p, int x, int y)
{
	char	**map;

	p->pl->pos_check = 0;
	map = m->map;
	if (x == 0 || y == 0 || x == m->x_max)
		error_handling(MAP_WALLS, p);
	if (map[x][y] == 'A')
		error_handling(MAP_WALLS, p);
	if (map[x][y - 1] == 'A')
		error_handling(MAP_WALLS, p);
	if (map[x][y + 1] == 'A')
		error_handling(MAP_WALLS, p);
	if (map[x + 1][y] == 'A')
		error_handling(MAP_WALLS, p);
	if (map[x - 1][y] == 'A')
		error_handling(MAP_WALLS, p);
}

// void	check_map(t_all *p, char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < p->map->x_max)
// 	{
// 		j = 0;
// 		while (j < p->map->y_max)
// 		{
// 			if (!(ft_strchr("012ANESW ", map[i][j])))
// 				error_handling(MAP_INVALID, p);
// 			j++;
// 		}
// 		i++;
// 	}
// 	check_walls(p->map, p);
// }


void	ft_checkmap_end(t_map *map, t_all *p)
{
	int i;
	int j;

	i = 0;
	while (i < map->x_max)
	{
		j = 0;
		while (j < map->y_max)
		{
			if (i != 0 && j != 1 && map->map[i][j] != '1' && map->map[i][j] != 'A')
				checkermap(map, p, i, j);
			j++;
		}
		i++;
	}
}
