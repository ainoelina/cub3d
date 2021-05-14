/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 13:31:29 by avuorio       #+#    #+#                 */
/*   Updated: 2021/05/14 14:04:32 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_extra(int error)
{
	if (error == PLAYER_NF)
		printf("Error\nPlayer position not defined.\n");
	if (error == MAP_INVALID)
		printf("Error\nMap input invalid.\n");
	if (error == COLOUR_MISSING)
		printf("Error\nMissing floor/ceiling input.\n");
	if (error == TEXTURE_MISSING)
		printf("Error\nMissing texture input.\n");
	if (error == RESOLUTION_MISSING)
		printf("Error\nMissing resolution input.\n");
	if (error == MAP_WALLS)
		printf("Error\nMap not closed by walls.\n");
	if (error == INVALID_INPUT)
		printf("Error\nInvalid input in .cub file.\n");
}

void	error_handling(int error, t_all *p)
{
	if (error == MLX_FUNCTION)
		printf("Error\nMlx function failed.\n");
	if (error == FD)
		printf("Error\nCould not open file.\n");
	if (error == MALLOC_FAIL)
		printf("Error\nMalloc function failed.\n");
	if (error == NO_MAP)
		printf("Error\nNo map found in file.\n");
	if (error == TEXTURE_DOUBLE)
		printf("Error\nTexture set twice.\n");
	if (error == RESOLUTION_DOUBLE)
		printf("Error\nResolution set twice.\n");
	if (error == RESOLUTION_INVALID)
		printf("Error\nResolution input invalid.\n");
	if (error == COLOUR_DOUBLE)
		printf("Error\nFloor/ceiling colour set twice.\n");
	if (error == COLOUR_INPUT)
		printf("Error\nFloor/ceiling colour input invalid.\n");
	if (error == ADDITIONAL_INPUT)
		printf("Error\nAdditional input after map.\n");
	if (error == PLAYER_DOUBLE)
		printf("Error\nPlayer position set twice.\n");
	error_extra(error);
	close_game(p);
}
