/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testmapparse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 10:45:09 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/23 12:41:19 by avuorio       ########   odam.nl         */
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

// void	create_map(char **array, t_param *p)
// {
// 	int	i;
// 	int	j;
// 	int	col;
// 	int	row;

// 	i = 0;
// 	row = 0;
// 	while (array[i])
// 	{
// 		j = 0;
// 		col = 0;
// 		while (array[row][col])
// 		{
// 			while (array[row][col] == ' ')
// 				col++;
// 			if (array[row][col])
// 			{
// 				p->world.map[i][j] = array[row][col];
// 				j++;
// 				col++;
// 			}
// 		}
// 		col = 0;
// 		row++;
// 		i++;
// 	}
// }

// int	count_col(t_param *p, char **array)
// {
// 	int	col_counter;
// 	int	y;
// 	int	empty;

// 	empty = 0;
// 	col_counter = 0;
// 	while (array[col_counter])
// 	{
// 		y = 0;
// 		while (array[col_counter][y] == ' ')
// 			y++;
// 		if (!array[col_counter][y])
// 			empty = 1;
// 		if (empty && array[col_counter][y])
// 			error_handling(MAP_INVALID, p);
// 		col_counter++;
// 	}
// 	return (col_counter);
// }

// int	count_row(char **array)
// {
// 	int	x;
// 	int	y;
// 	int	row_counter;
// 	int	rows;

// 	x = 0;
// 	row_counter = 0;
// 	while (array[x])
// 	{
// 		y = 0;
// 		rows = 0;
// 		while (array[x][y])
// 		{
// 			if (array[x][y] != ' ')
// 				rows++;
// 			y++;
// 		}
// 		if (rows > row_counter)
// 			row_counter = rows;
// 		x++;
// 	}
// 	return (row_counter);
// }

// void	map_init(t_param *p)
// {
// 	int	col;
// 	int	row;

// 	col = 0;
// 	p->world.col = 0;
// 	p->world.row = 0;
// 	p->world.map = malloc(sizeof(int *) * (p->world.max_row + 1));
// 	while (col < p->world.max_row)
// 	{
// 		p->world.map[col] = malloc(sizeof(int) * (p->world.max_col));
// 		row = 0;
// 		while (row < p->world.max_col)
// 		{
// 			p->world.map[col][row] = 'A';
// 			row++;
// 			if (row == p->world.max_col)
// 				p->world.map[col][row] = '\0';
// 		}
// 		col++;
// 	}
// }


int		counter(t_param *p, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'W' || line[i] == 'S'
			|| line[i] == 'E')
			count++;
		i++;
	}
	if (p->map.x != 0 && p->map.x != count)
		return (-1);
	return (count);
}

char		*max_y(t_param *p, char *line, int *i)
{
	char	*str;
	int		j;

	str = malloc(sizeof(char) * (counter(p, line) + 1));
	j = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == 'W' || line[*i] == 'N' || line[*i] == 'S' || line[*i] == 'E')
		{
			str[j] = line[*i];
			j++;
		}
		else if (line[*i] == '2')
		{
			str[j] = line[*i];
			p->map.sprite++;
			j++;
		}
		else if (line[*i] == ' ')
		{
			free(str);
			return (NULL);
		}
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

void	parse_map1(t_param *p, char *line, int *i)
{
	char 	**temp;
	int		j;

	p->err = 1;
	temp = malloc(sizeof(char *) * (p->map.y + 2));
	if (!temp)
		error_handling(MAP_MALLOC, p);
	j = 0;
	while (j < p->map.y)
	{
		temp[j] = p->map.map[j];
		j++;
	}
	temp[p->map.y] = max_y(p, line, i);
	if (temp[p->map.y] == NULL)
		error_handling(MAP_INVALID, p);
	temp[p->map.y + 1] = NULL;
	if (p->map.y > 0)
		free(p->map.map);
	p->map.map = temp;
	p->map.y++;
	p->map.x = counter(p, line);
	printf("map line now is %s\n", p->map.map[j]);
// 	p->world.max_row = count_col(p, map_array);
// 	p->world.max_col = count_row(map_array);
// 	printf("max row is %i\n", p->world.max_row);
// 	printf("max col is %i\n", p->world.max_col);
// 	map_init(p);
// 	create_map(map_array, p);
// 	define_position(p);
// 	printf("player position now is x = %f y = %f\n", p->pl.x_pos, p->pl.y_pos);
// //	check_map(p, p->pl.x_pos, p->pl.y_pos);
}
