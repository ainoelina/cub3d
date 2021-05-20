/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkmap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 17:33:36 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/20 11:22:32 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	check_mapchar(t_all *p, char **map, int i, int j)
// {
// 	if ((i == 0 || j == 0) && (map[i][j] != '1' && map[i][j] != ' '))
// 		error_handling(MAP_WALLS, p);
// 	if (map[i][j] == '\0' && map[i][j - 1] != '1')
// 		error_handling(MAP_WALLS, p);
	
// }

// void	map_checker(t_all *p, char **map)
// {
// 	char	**temp;
// 	int		i;
// 	int		j;

// 	temp = map;
// 	i = 0;
// 	while (i < p->map->x_max)
// 	{
// 		j = 0;
// 		printf("first %s\n", temp[i]);
// 		while (j < p->map->y_max)
// 		{
// 			if (temp[i][j] != '1')
// 				check_mapchar(p, temp, i, j);
// 			j++;
// 		}
// 		printf("string is %s\n", temp[i]);
// 		i++;
// 	}
// }
