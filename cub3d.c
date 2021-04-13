/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 09:49:34 by avuorio       #+#    #+#                 */
/*   Updated: 2021/04/13 17:16:26 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_screen(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->screenw, mlx->screenh);
	mlx->img_addr = (int *)mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->sizeline, &mlx->endian);
}

int	run_game(t_all *p)
{
	init_screen(p->mlx);
	move(p);
	raycast(p);
	mlx_put_image_to_window(p->mlx->mlx_ptr, p->mlx->win_ptr,
		p->mlx->img_ptr, 0, 0);
	return (0);
}

void	start_game(t_all *p, char *cub, int screenshot)
{
	parser(p, cub);
	p->mlx->mlx_ptr = mlx_init();
	handle_texture(p, p->txt);
	if (screenshot == 1)
		printf("make screenshot\n");
	p->mlx->win_ptr = mlx_new_window(p->mlx->mlx_ptr, p->mlx->screenw,
			p->mlx->screenh, "cub3d");
	mlx_hook(p->mlx->win_ptr, 2, 0, key_pressed, p);
	mlx_hook(p->mlx->win_ptr, 3, 0, key_released, p);
	mlx_hook(p->mlx->win_ptr, 17, 0, close_game, p);
	mlx_loop_hook(p->mlx->mlx_ptr, run_game, p);
	mlx_loop(p->mlx->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && file_check(argv[1], 'c'))
		init_all(argv[1], 0);
	else if (argc == 3 && file_check(argv[1], 'c')
		&& save_check(argv[2], "--save"))
		init_all(argv[1], 1);
	else
		printf("ERROR:\nInvalid arguments.\n");
	return (0);
}
