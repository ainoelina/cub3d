/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:39:34 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/26 11:58:34 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_handling2(int error)
{
	if (error == PLAYER_NF)
		printf("ERROR:\nPlayer position not defined.\n");
	if (error == PLAYER_DOUBLE)
		printf("ERROR:\nPlayer position set twice.\n");
	if (error == MISSING_INPUT)
		printf("ERROR:\nMissing necessary input.\n");
	if (error == MAP_WALLS)
		printf("ERROR:\nMap not closed by walls.\n");
	if (error == SPRITE_MALLOC)
		printf("ERROR:\nMallocing for sprites failed.\n");
	if (error == BUF_MALLOC)
		printf("ERROR:\nMallocing for buffer failes.\n");
}

void	error_handling(int error, t_param *p)
{
	if (error == FD)
		printf("ERROR:\nCould not open file.\n");
	if (error == RGB_STRING)
		printf("ERROR:\nInvalid color input.\n");
	if (error == TXT_DOUBLE)
		printf("ERROR:\nTexture set twice.\n");
	if (error == XPM_MALLOC)
		printf("ERROR:\nMallocing for .xpm file failed.\n");
	if (error == MAP_MALLOC)
		printf("ERROR:\nMallocing for map failed.\n");
	if (error == MAP_INVALID)
		printf("ERROR:\nMap input invalid.\n");
	if (error == RES_DOUBLE)
		printf("ERROR:\nResolution set twice.\n");
	if (error == RES_INVALID)
		printf("ERROR:\nInvalid resolution input.\n");
	if (error == COLOR_DOUBLE)
		printf("ERROR:\nFloor/ceiling color set twice.\n");
	if (error == COLOR_INPUT)
		printf("ERROR:\nFloor/ceiling color input invalid.\n");
	error_handling2(error);
	close_game(p);
}

/*could add int win to call destroy win funct*/

int	close_game(t_param *p)
{
	int i;
	printf("\nCLOSING GAME\n");
	free(p->text.north);
	free(p->text.south);
	free(p->text.east);
	free(p->text.west);
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
	free(p->mlx.ptr);
	exit(0);
	return (1);
}
