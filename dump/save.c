// void	draw_stripe(t_walls *walls, t_mlx *mlx, t_all *p, int stripe)
// {
// 	double	step;
// 	double	pos;
// 	int		i;
// 	int		*text;

// 	i = 0;
// 	step = 1.0 * walls->heigth / walls->line_h;
// 	pos = (walls->start - p->mlx->screenh / 2 + walls->line_h / 2) * step;
// 	text = walls->text;
// 	while (i < walls->start)
// 	{
// 		*(mlx->img_addr + stripe + i * mlx->sizeline / 4) = p->txt->ceiling;
// 		i++;
// 	}
// 	while (i <= walls->end)
// 	{
// 		*(mlx->img_addr + stripe + i + mlx->sizeline / 4) = *(text
// 			+ walls->texture + (int)pos * walls->sl / 4);
// 		pos = pos + step;
// 		i++;
// 	}
// 	while (i < mlx->screenh)
// 	{
// 		*(mlx->img_addr + stripe + i * mlx->sizeline / 4) = p->txt->floor;
// 		i++;
// 	}
// }

// void	handle_texture(t_all *p, t_texture *txt)
// {
// 	txt->northptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
// 			txt->north_tex, &txt->n_w, &txt->north_h);
// 	txt->eastptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
// 			txt->east_tex, &(txt->e_w), &(txt->east_h));
// 	txt->southptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
// 			txt->south_tex, &(txt->s_w), &(txt->south_h));
// 	txt->westptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
// 			txt->west_tex, &(txt->w_w), &(txt->west_h));
// 	txt->sprptr = mlx_xpm_file_to_image(p->mlx->mlx_ptr,
// 			txt->spr_tex, &(txt->sp_w), &(txt->spr_h));
// 	txt->north = (int *)mlx_get_data_addr(txt->northptr,
// 			&(txt->n_sb), &(txt->north_sl), &(txt->n_ed));
// 	txt->east = (int *)mlx_get_data_addr(txt->eastptr,
// 			&(txt->e_sb), &(txt->east_sl), &(txt->e_ed));
// 	txt->south = (int *)mlx_get_data_addr(txt->southptr,
// 			&(txt->s_sb), &(txt->south_sl), &(txt->s_ed));
// 	txt->west = (int *)mlx_get_data_addr(txt->westptr,
// 			&(txt->w_sb), &(txt->west_sl), &(txt->w_ed));
// 	txt->sprite = (int *)mlx_get_data_addr(txt->sprptr,
// 			&(txt->sp_sb), &(txt->spr_sl), &(txt->sp_ed));
// }