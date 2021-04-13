/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 12:56:31 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/13 17:17:13 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_all *p)
{
	int	i;

	free(p->txt->north_tex);
	free(p->txt->east_tex);
	free(p->txt->south_tex);
	free(p->txt->west_tex);
	free(p->txt->spr_tex);
	i = 0;
	if (p->lines)
	{
		while (p->lines[i])
		{
			free(p->lines[i]);
			i++;
		}
		free(p->lines);
	}
	free(p->mlx->mlx_ptr);
	exit(0);
	return (1);
}

int	key_released(int key, t_all *p)
{
	if (key == A)
		p->move->left = 0;
	if (key == D)
		p->move->right = 0;
	if (key == W)
		p->move->forw = 0;
	if (key == S)
		p->move->backw = 0;
	if (key == LEFT)
		p->move->rotate_left = 0;
	if (key == RIGHT)
		p->move->rotate_right = 0;
	return (1);
}

int	key_pressed(int key, t_all *p)
{
	if (key == ESC)
		close_game(p);
	if (key == A)
		p->move->left = 1;
	if (key == D)
		p->move->right = 1;
	if (key == W)
		p->move->forw = 1;
	if (key == S)
		p->move->backw = 1;
	if (key == LEFT)
		p->move->rotate_left = 1;
	if (key == RIGHT)
		p->move->rotate_right = 1;
	return (1);
}
