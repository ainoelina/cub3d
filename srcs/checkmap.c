/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkmap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 17:33:36 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/18 17:47:22 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int




// int		check_around(char **map, int x, int y)
// {
// 	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
// 		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' '
// 		|| !map[y - 1][x - 1] || map[y - 1][x - 1] == ' '
// 		|| !map[y + 1][x - 1] || map[y + 1][x - 1] == ' '
// 		|| !map[y - 1][x + 1] || map[y - 1][x + 1] == ' '
// 		|| !map[y + 1][x + 1] || map[y + 1][x + 1] == ' ')
// 		return (0);
// 	return (1);
// }

// int		invalid_map(char **map, int y, int map_height, int line_len)
// {
// 	int		x;
// 	int		next_len;
// 	int		previous_len;

// 	x = -1;
// 	if (y > 0)
// 		previous_len = ft_strlen(map[y - 1]);
// 	next_len = y + 1 != map_height ? (int)ft_strlen(map[y + 1]) : 0;
// 	while (map[y][++x])
// 	{
// 		if ((ft_strchr(NOT_WALL, map[y][x]) != NULL) && (y == 0 || x == 0
// 			|| y == (map_height - 1) || x == (line_len - 1)
// 			|| x - 1 > previous_len || x + 1 > next_len
// 			|| !check_around(map, x, y)))
// 		{
// 			error_msg_parsing(MAP_NOT_CLOSED_ERROR);
// 			return (1);
// 		}
// 		if (ft_strchr(ELEMENTS_CHARSET, map[y][x]) == NULL)
// 		{
// 			error_msg(UNKNOWN_ELEMENT_ERROR);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// void	check_the_map(char **map)
// {

// }

// int		check_map(char **map)
// {
// 	int		y;
// 	int		line_len;
// 	int		map_height;

// 	y = -1;
// 	map_height = 0;
// 	while (map[map_height])
// 		map_height++;
// 	while (map[++y])
// 	{
// 		line_len = ft_strlen(map[y]);
// 		if (invalid_map(map, y, map_height, line_len))
// 			return (0);
// 	}
// 	return (1);
// }

void	map_checker(t_all *p, char **map)
{
	char	**temp;
	int		i;
	int		j;

	temp = map;
	i = p->map->x_max;
	while (i > 0)
	{
		j = 0;
		printf("first %s\n", map[i]);
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'A')
				map[i][j] = '\0';
			j++;
		}
		printf("string is %s\n", map[i]);
		i--;
	}
}