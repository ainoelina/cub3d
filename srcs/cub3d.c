/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avuorio <avuorio@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/18 11:00:07 by avuorio       #+#    #+#                 */
/*   Updated: 2021/03/31 13:12:37 by avuorio       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_screen(t_param *p)
{
	p->img.ptr = mlx_new_image(p->mlx.ptr, p->win.width, p->win.heigth);
	p->img.addr = (int *)mlx_get_data_addr(p->img.ptr, &p->img.bpp,
			&p->img.s_len, &p->img.endian);
}

int 	update(t_param *p)
{
	init_screen(p);
//	fill(p);
	raycast(p);
	mlx_put_image_to_window(p->mlx.ptr, p->win.ptr, p->img.ptr, 0, 0);
	free(p->img.ptr);
	free(p->img.addr);
	return (0);
}

void	start_point(t_param p, char *file)
{
	printf("\nthis is START POINT\n");
	p.mlx.ptr = mlx_init();
	if (parsing(&p, file) == -1)
		close_game(&p);
//	printf("texture path now is %s\n", p.text.n_txt);
	handle_textures(&p);
	p.win.ptr = mlx_new_window(p.mlx.ptr, p.win.width, p.win.heigth, "cub3d");
	//img_to_win(&p);
//	raycast(&p);
//	printf("wehre is the problemmmm\n");
	mlx_hook(p.win.ptr, 2, 0, key, &p);
	mlx_hook(p.win.ptr, 17, 0, close_game, &p);
	mlx_loop_hook(p.mlx.ptr, update, &p);
	mlx_loop(p.mlx.ptr);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && cub_check(argv[1]))
		init_param(argv[1]);
	else
		printf("ERROR:\nArguments invalid.\n");
	return (0);
}
