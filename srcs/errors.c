/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 13:31:29 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/13 17:21:54 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_extra(int error)
{
	if (error == PLAYER_NF)
		printf("ERROR:\nPlayer position not defined.\n");
	if (error == MAP_INVALID)
		printf("ERROR:\nInvalid character found in map.\n");
}

void	error_handling(int error, t_all *p)
{
	if (error == MLX_FUNCTION)
		printf("ERROR:\nMlx function failed.\n");
	if (error == FD)
		printf("ERROR:\nCould not open file.\n");
	if (error == MALLOC_FAIL)
		printf("ERROR:\nMalloc function failed.\n");
	if (error == NO_MAP)
		printf("ERROR:\nNo map found in file.\n");
	if (error == TEXTURE_DOUBLE)
		printf("ERROR:\nTexture set twice.\n");
	if (error == RESOLUTION_DOUBLE)
		printf("ERROR:\nResolution set twice.\n");
	if (error == RESOLUTION_INVALID)
		printf("ERROR:\nResolution input invalid.\n");
	if (error == COLOUR_DOUBLE)
		printf("ERROR:\nFloor/ceiling colour set twice.\n");
	if (error == COLOUR_INPUT)
		printf("ERROR:\nFloor/ceiling colour input invalid.\n");
	if (error == ADDITIONAL_INPUT)
		printf("ERROR:\nAdditional input after map.\n");
	if (error == PLAYER_DOUBLE)
		printf("ERROR:\nPlayer position set twice.\n");
	error_extra(error);
	close_game(p);
}
