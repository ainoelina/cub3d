/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 10:54:54 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/16 17:36:34 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_horizontal(t_param *p, int direction)
{
	if (direction == -1 && p)
		printf("key is A\n");
	if (direction == 1 && p)
		printf("key is D\n");
}

void	move_vertical(t_param *p, int direction)
{
	if (direction == -1 && p)
		printf("key is S\n");
	if (direction == 1 && p)
		printf("key is W\n");
}
void	rotate(t_param *p, int direction)
{
	if (direction == -1 && p)
		printf("key is LEFT\n");
	if (direction == 1 && p)
		printf("key is RIGHT\n");
}

int	key(int key, t_param *p)
{
	printf("\nchecking the KEY\n");
	if (key == ESC)
		close_game(p);
	if (key == A)
		move_horizontal(p, -1);
	if (key == D)
		move_horizontal(p, 1);
	if (key == W)
		move_vertical(p, 1);
	if (key == S)
		move_vertical(p, -1);
	if (key == LEFT)
		rotate(p, -1);
	if (key == RIGHT)
		rotate(p, 1);
	return (1);
}
