/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 09:26:49 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/18 17:30:16 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_from_position(t_all *p, int x, int y)
{
	char	**temp;

	temp = p->map->map;
	if (temp[x][y] == '1' || temp[x][y] == 'O' || temp[x][y] == '2')
		return ;
	if (x == 0 || y == 0 || x == p->map->x_max)
		error_handling(MAP_WALLS, p);
	if (temp[x][y] == 'A')
		error_handling(MAP_WALLS, p);
	if (temp[x][y] == '0')
		temp[x][y] = 'O';
	check_from_position(p, x + 1, y);
	check_from_position(p, x, y + 1);
	check_from_position(p, x - 1, y);
	check_from_position(p, x, y - 1);
}

int	check_mapchar(t_all *p, char **map, int i, int j)
{
	if (map[i][j] == 'A' && (map[i][j - 1] != '1' && map[i][j - 1] != 'A'))
		return (-1);
	if (i == p->map->x_max - 1 && j == p->map->y_max - 1 && (map[i][j] != '1'
		&& map[i][j] != 'A'))
		{ printf("how come not\n");
		return (-1);
		}
	if (i == 0 && j == 0 && (map[i][j] != '1' && map[i][j] != ' '))
		return (-1);
	return (1);
}

void	map_check(t_all *p, t_map *m, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->x_max)
	{
		j = 0;
		while (j < m->y_max)
		{
			while (map[i][j] == ' ')
				j++;
			if (!check_mapchar(p, map, i, j))
			{

				error_handling(MAP_WALLS, p);
			}
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2'
				&& map[i][j] != 'A' && map[i][j] != 'N' && map[i][j] != 'E'
				&& map[i][j] != 'S' && map[i][j] != 'W')
				error_handling(MAP_INVALID, p);
			j++;
		}
		i++;
	}
	check_from_position(p, p->pl->x, p->pl->y);
}

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

// void	checkermap(t_map *m, t_all *p, int x, int y)
// {
// 	char	**map;

// 	p->pl->pos_check = 0;
// 	map = m->map;
// 	if (x == 0 || y == 0 || x == m->x_max)
// 		error_handling(MAP_WALLS, p);
// 	if (map[x][y] == 'A')
// 		error_handling(MAP_WALLS, p);
// 	if (map[x][y - 1] == 'A')
// 		error_handling(MAP_WALLS, p);
// 	if (map[x][y + 1] == 'A')
// 		error_handling(MAP_WALLS, p);
// 	if (map[x + 1][y] == 'A')
// 		error_handling(MAP_WALLS, p);
// 	if (map[x - 1][y] == 'A')
// 		error_handling(MAP_WALLS, p);
// }

// // void	check_map(t_all *p, char **map)
// // {
// // 	int	i;
// // 	int	j;

// // 	i = 0;
// // 	while (i < p->map->x_max)
// // 	{
// // 		j = 0;
// // 		while (j < p->map->y_max)
// // 		{
// // 			if (!(ft_strchr("012ANESW ", map[i][j])))
// // 				error_handling(MAP_INVALID, p);
// // 			j++;
// // 		}
// // 		i++;
// // 	}
// // 	check_walls(p->map, p);
// // }


// void	ft_checkmap_end(t_map *map, t_all *p)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < map->x_max)
// 	{
// 		j = 0;
// 		while (j < map->y_max)
// 		{
// 			if (i != 0 && j != 1 && map->map[i][j] != '1' && map->map[i][j] != 'A')
// 				checkermap(map, p, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// }
