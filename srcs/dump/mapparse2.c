/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 14:18:18 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/03 12:17:08 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_counter(char *line)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
			|| line[i] == 'W')
			counter++;
		i++;
	}
	return (counter);
}

char	*copy_map_contents(t_param *p, int *i, char *line, char *map)
{
	int	k;

	k = 0;
	while (line[*i])
	{
		if (line[*i] == '1' || line[*i] == '0' || line[*i] == 'N'
			|| line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W')
		{
			map[k] = line[*i];
			k++;
		}
		else if (line[*i] == '2')
		{
			map[k] = line[*i];
			k++;
			p->map.sprite++;
		}
		else if (line[*i] != ' ')
			return (NULL);
		(*i)++;
	}
	map[k] = '\0';
	return (map);
}

char	*define_map(t_param *p, char *line, int *i)
{
	char	*map;

	map = malloc(sizeof(char) * (map_counter(line) + 1));
	if (!map)
		return (NULL);
	map = copy_map_contents(p, i, line, map);
	if (map == NULL)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	parse_map(t_param *p, char *line, int *i)
{
	char	**temp;
	int		j;

	temp = malloc(sizeof(char *) * (p->map.y + 2));
	if (!temp)
		error_handling(MAP_MALLOC, p);
	j = 0;
	while (j < p->map.y)
	{
		temp[j] = p->map.map[j];
		j++;
	}
	temp[p->map.y] = define_map(p, line, i);
	if (temp[p->map.y] == NULL)
	{
		free(temp);
		error_handling(MAP_INVALID, p);
	}
	temp[p->map.y + 1] = NULL;
	if (p->map.y > 0)
		free(p->map.map);
	p->map.map = temp;
	p->map.y++;
	p->map.x = map_counter(line);
	return (0);
}
