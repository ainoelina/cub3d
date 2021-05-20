/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 09:26:49 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/20 12:16:08 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_surroundings(t_map *m, t_all *p, int x, int y)
{
	char	**map;

	p->pl->pos_check = 0;
	map = m->map;
	if (map[x][y] == ' ' && (map[x][y + 1] != '1' && map[x][y + 1] != ' '))
		error_handling(MAP_WALLS, p);
	if ((map[x][y] == '0' || map[x][y] == '2' || map[x][y] == ' ')
		&& map[x][y + 1] == '\0')
		error_handling(MAP_WALLS, p);
	if (x == 0 && (map[x][y] != '1' && map[x][y] != ' '))
		error_handling(MAP_WALLS, p);
	if ((map[x][y] == '0' || map[x][y] == '2') && y == 0)
		error_handling(MAP_WALLS, p);
	if ((map[x][y] == '0' || map[x][y] == '2') && map[x][y - 1] == ' ')
		error_handling(MAP_WALLS, p);
	if (map[x][y] == ' ' && (map[x][y + 1] == '0' || map[x][y + 1] == '2'))
		error_handling(MAP_WALLS, p);
}


void	check_map(t_map *map, t_all *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->x_max)
	{
		j = 0;
		while (j < map->y_max)
		{
			if (map->map[i][j] != '1' && map->map[i][j] != 'A'
			&& map->map[i][j] != '\0')
				check_surroundings(map, p, i, j);
			j++;
		}
		i++;
	}
}
