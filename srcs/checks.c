/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 16:53:38 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/29 15:58:08 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_input(t_param *p)
{
	if (p->text.n_txt == NULL || p->text.e_txt == NULL || p->text.s_txt == NULL
		|| p->text.w_txt == NULL || p->text.sp_txt == NULL || p->text.floor == 0
		|| p->text.ceiling == 0 || p->win.width == 0 || p->win.heigth == 0)
		error_handling(MISSING_INPUT, p);
}

// int	check_map(t_param *p)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < p->world.max_y)
// 	{
// 			printf("am i here at any point\n");
// 		j = 0;
// 		while (j < p->world.max_x)
// 		{
// 			printf("or am i here at any point\n");
// 			if (p->world.map[i][j] != '1' && i == 0)
// 				error_handling(MAP_WALLS, p);
// 			else if (p->world.map[i][j] != '1' && i == p->world.max_y - 1)
// 				error_handling(MAP_WALLS, p);
// 			else if (p->world.map[i][j] != '1' && j == 0)
// 				error_handling(MAP_WALLS, p);
// 			else if (p->world.map[i][j] != '1' && j == p->world.max_x - 1)
// 				error_handling(MAP_WALLS, p);
// 			j++;
// 		}
// 		i++;
// 	}

// 	return (1);
// }

void	check_map(t_param *p, int x, int y)
{
	char	**map;

	p->pl.pos = 0;
	map = p->world.map;
	if (map[x][y] == '-' || map[x][y] == 'F' || map[x][y] == 'E')
		return ;
	if (x == 0 || y == 0 || x == p->world.max_row)
		error_handling(MAP_WALLS, p);
	if (map[x][y] == 'A')
		error_handling(MAP_WALLS, p);
	if (map[x][y] == 0)
		map[x][y] = 'E';
	if (map[x][y] == 1)
		map[x][y] = '-';
	if (map[x][y] == 2)
		map[x][y] = 'F';
	printf("%s\n", map[x]);
	check_map(p, x + 1, y);
	check_map(p, x, y + 1);
	check_map(p, x - 1, y);
	check_map(p, x, y - 1);
}
