/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 13:48:20 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/12 10:37:12 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(int *i, char *line)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n'
		|| line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f')
		(*i)++;
}

void	copy_lines(char **lines, int *index, char **save)
{
	if (save)
	{
		while (save[*index])
		{
			lines[*index] = save[*index];
			(*index)++;
		}
	}
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
