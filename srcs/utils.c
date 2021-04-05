/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:41:12 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/31 09:55:16 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_check(char *cub)
{
	int	i;

	i = 0;
	while (cub[i])
		i++;
	if (cub[i - 1] == 'b' && cub[i - 2] == 'u' && cub[i - 3] == 'c'
		&& cub[i - 4] == '.')
		return (1);
	return (0);
}

int	my_atoi(char *line, int *i)
{
	int	n;

	n = 0;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		n = (n * 10) + (line[*i] - 48);
		(*i)++;
	}
	return (n);
}

void	skip_spaces(int *i, char *line)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n'
	|| line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f')
		(*i)++;
}

void	copier(char **lines, int *j, char **temp)
{
	if (temp)
	{
		while (temp[*j])
		{
			lines[*j] = temp[*j];
			(*j)++;
		}
	}
}
