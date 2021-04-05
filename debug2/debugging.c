#include "../srcs/cub3d.h"
#include "../mlx/mlx.h"

void my_mlx_pixel_put(t_param *p, int x, int y, unsigned int color)
{
	int    *dst;

    dst = p->img.addr + (y * p->img.s_len + x * (p->img.bpp / 8));
    *(unsigned int*)dst = color;
}
void	init_position(t_param *p)
{
	p->pl.forw = 0;
	p->pl.back = 0;
	p->pl.l = 0;
	p->pl.r = 0;
	p->pl.r_rot = 0;
	p->pl.l_rot = 0;
}

void	init_player(char c, int x, int y, t_param *p)
{
	if (c != 'N' && c != 'E' && c != 'S' && c != 'W')
		error_handling(MAP_INVALID, p);
	if (p->pl.pos > 0)
		error_handling(PLAYER_DOUBLE, p);
	p->pl.x_pos = x + 0.5;
	p->pl.y_pos = y + 0.5;
	if (c == 'N' || c == 'S')
	{
		p->pl.x_dir = 1;
		p->pl.y_dir = 0;
		if (c == 'N')
			p->pl.x_dir = p->pl.x_dir * -1;
	}
	if (c == 'W' || c == 'E')
	{
		p->pl.x_dir = 0;
		p->pl.y_dir = 1;
		if (c == 'W')
			p->pl.y_dir = p->pl.y_dir * -1;
	}
	init_position(p);
}

int	check_char(char	c, int x, int y, t_param *p)
{
	if (c != '1' && c != '2' && c != '0' && c != 'A')
	{
		init_player(c, x, y, p);
		return (1);
	}
	return (0);
}

/*
** changed the loops from i <= and j <= to <
** see that if you run into problems later on
*/

void	define_position(t_param *p)
{
	int	i;
	int	j;

	i = 0;
	p->pl.pos = 0;
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			p->pl.pos = p->pl.pos + check_char(p->world.map[i][j], i, j, p);
			j++;
		}
		i++;
	}
	if (p->pl.pos == 0)
		error_handling(PLAYER_NF, p);
}

void fill(t_param *p)
{
	int i = 0;
	int j = 0;

	while (i < p->world.max_row)
	{
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '1')
				my_mlx_pixel_put(p, j, i, WHITE);
			if (p->world.map[i][j] == '0')
				my_mlx_pixel_put(p, j, i, YELLOW);
			if (p->world.map[i][j] == 'N')
				my_mlx_pixel_put(p, j, i, RED);
			if (p->world.map[i][j] == 'E')
				my_mlx_pixel_put(p, j, i, BLUE);
			if (p->world.map[i][j] == 'S')
				my_mlx_pixel_put(p, j, i, CYAN);
			if (p->world.map[i][j] == 'W')
				my_mlx_pixel_put(p, j, i, GREEN);

			j++;
		}
		j = 0;
		i++;
	}
}

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

char	*null_return(char *string)
{
	free(string);
	return (0);
}

int	minus_return(char *buffer)
{
	free(buffer);
	return (-1);
}

size_t	str_len(char *str)
{
	size_t	i;

	if (str == 0)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *d, const void *s, size_t len)
{
	char	*dest;
	char	*src;
	size_t	i;

	dest = (char *)d;
	src = (char *)s;
	if (dest > src)
	{
		while (len > 0)
		{
			len--;
			dest[len] = src[len];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (d);
}

char	*join_strings(char *rest, char *buffer)
{
	size_t		len1;
	size_t		len2;
	size_t		len;
	char		*new;

	if (rest == NULL && buffer == NULL)
		return (NULL);
	len1 = str_len(rest);
	len2 = str_len(buffer);
	len = len1 + len2 + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
	{
		free((char *)rest);
		free((char *)buffer);
		return (NULL);
	}
	ft_memmove(new, rest, len1);
	ft_memmove(new + len1, buffer, len2);
	new[len - 1] = '\0';
	free((char *)rest);
	return (new);
}

static char	*create_rest(char *rest)
{
	char	*remain;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (rest == NULL)
		return (NULL);
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	if (rest[i] == 0)
		return (null_return(rest));
	remain = malloc(sizeof(char) * ((str_len(rest) - i) + 1));
	if (!remain)
		return (0);
	i++;
	while (rest[i] != '\0')
	{
		remain[j] = rest[i];
		j++;
		i++;
	}
	remain[j] = '\0';
	free(rest);
	return (remain);
}

static char	*create_line(char *string)
{
	char	*line;
	size_t	i;

	if (string == NULL)
		return (NULL);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	contains_newline(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	return_value(int reader)
{
	if (reader == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest;
	char		*buffer;
	int			reader;

	reader = 1;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!contains_newline(rest) && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
			return (minus_return(buffer));
		buffer[reader] = '\0';
		rest = join_strings(rest, buffer);
		if (!rest)
			return (-1);
	}
	free(buffer);
	*line = create_line(rest);
	rest = create_rest(rest);
	return (return_value(reader));
}


void	check_input(t_param *p)
{
	if (p->text.n_txt == NULL || p->text.e_txt == NULL || p->text.s_txt == NULL
		|| p->text.w_txt == NULL || p->text.sp_txt == NULL || p->text.floor == 0
		|| p->text.ceiling == 0 || p->win.x == 0 || p->win.y == 0)
		error_handling(MISSING_INPUT, p);
}

// int	check_map(t_param *p)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < p->world.max_y)
// 	{
// 			printf("am i here at any point\n");
// 		j = 0;
// 		while (j < p->world.max_x)
// 		{
// 			printf("or am i here at any point\n");
// 			if (p->world.map[i][j] != '1' && i == 0)
// 				error_handling(MAP_WALLS, p);
// 			else if (p->world.map[i][j] != '1' && i == p->world.max_y - 1)
// 				error_handling(MAP_WALLS, p);
// 			else if (p->world.map[i][j] != '1' && j == 0)
// 				error_handling(MAP_WALLS, p);
// 			else if (p->world.map[i][j] != '1' && j == p->world.max_x - 1)
// 				error_handling(MAP_WALLS, p);
// 			j++;
// 		}
// 		i++;
// 	}

// 	return (1);
// }

void	check_map(t_param *p, int x, int y)
{
	char	**map;

	p->pl.pos = 0;
	map = p->world.map;
	if (map[x][y] == '-' || map[x][y] == 'F' || map[x][y] == 'E')
		return ;
	if (x == 0 || y == 0 || x == p->world.max_row)
		error_handling(MAP_WALLS, p);
	if (map[x][y] == 'A')
		error_handling(MAP_WALLS, p);
	if (map[x][y] == 0)
		map[x][y] = 'E';
	if (map[x][y] == 1)
		map[x][y] = '-';
	if (map[x][y] == 2)
		map[x][y] = 'F';
	printf("%s\n", map[x]);
	check_map(p, x + 1, y);
	check_map(p, x, y + 1);
	check_map(p, x - 1, y);
	check_map(p, x, y - 1);
}

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
	printf("\nCLOSING GAME\n");
	free(p->text.n);
	free(p->text.s);
	free(p->text.e);
	free(p->text.w);
	free(p->mlx.ptr);
	exit(0);
	return (1);
}

void	init_textures(t_text *text)
{
	text->n = NULL;
	text->s = NULL;
	text->e = NULL;
	text->w = NULL;
	text->n_txt = NULL;
	text->e_txt = NULL;
	text->s_txt = NULL;
	text->w_txt = NULL;
	text->sp_txt = NULL;
	text->floor = 0;
	text->ceiling = 0;
}

void	init_map(t_map *map)
{
	map->y = 0;
	map-> x = 0;
	map->sprite = 0;
	map->map = NULL;
}

void	init_param(char *file)
{
	t_param		p;
	t_mlx		mlx;
	t_img		img;
	t_win		win;
	t_text		text;
	t_map		map;
	t_sprites	sprite;

	p.err = 0;
	mlx.ptr = NULL;
	img.ptr = NULL;
	img.addr = NULL;
	win.ptr = NULL;
	win.x = 0;
	win.y = 0;
	win.res_check = 0;
	sprite.spr = NULL;
	init_map(&map);
	init_textures(&text);
	p.sprites = sprite;
	p.map = map;
	p.mlx = mlx;
	p.img = img;
	p.win = win;
	p.text = text;
	start_point(p, file);
}

int	key_check(int key, void *arg)
{
	printf("\nchecking the KEY\n");
	if (key == 53)
		close_game(arg);
	return (1);
}

int	count_sprites(t_param *p)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	printf("map line %s\n", p->world.map[i]);
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	malloc_sprites(t_param *p, t_spr *sprites)
{
	sprites = malloc(sizeof(t_spr) * p->sprites.n);
	if (!sprites)
		error_handling(SPRITE_MALLOC, p);
	p->sprites.order = malloc(sizeof(int) * p->sprites.n);
	if (!p->sprites.order)
		error_handling(SPRITE_MALLOC, p);
}

t_spr	*parse_sprites(t_param *p)
{
	int		i;
	int		j;
	t_spr	*sprites;
	int		pos;

	sprites = NULL;
	p->sprites.n = count_sprites(p);
	malloc_sprites(p, sprites);
	i = 0;
	pos = 0;
	while (i < p->world.max_row)
	{
		j = 0;
		while (j < p->world.max_col)
		{
			if (p->world.map[i][j] == '2')
			{
				sprites[pos].x = i;
				sprites[pos].y = j;
				pos++;
			}
			j++;
		}
		i++;
	}
	return (sprites);
}

void	create_map(char **array, t_param *p)
{
	int	i;
	int	j;
	int	col;
	int	row;

	i = 0;
	row = 0;
	while (array[i])
	{
		j = 0;
		col = 0;
		while (array[row][col])
		{
			while (array[row][col] == ' ')
				col++;
			if (array[row][col])
			{
				p->world.map[i][j] = array[row][col];
				j++;
				col++;
			}
		}
		col = 0;
		row++;
		i++;
	}
}

int	count_col(t_param *p, char **array)
{
	int	x_counter;
	int	y;
	int	empty;

	empty = 0;
	x_counter = 0;
	while (array[x_counter])
	{
		y = 0;
		while (array[x_counter][y] == ' ')
			y++;
		if (!array[x_counter][y])
			empty = 1;
		if (empty && array[x_counter][y])
			error_handling(MAP_INVALID, p);
		x_counter++;
	}
	return (x_counter);
}

int	count_row(char **array)
{
	int	x;
	int	y;
	int	y_counter;
	int	rows;

	x = 0;
	y_counter = 0;
	while (array[x])
	{
		y = 0;
		rows = 0;
		while (array[x][y])
		{
			if (array[x][y] != ' ')
				rows++;
			y++;
		}
		if (rows > y_counter)
			y_counter = rows;
		x++;
	}
	return (y_counter);
}

void	map_init(t_param *p)
{
	int	col;
	int	row;

	col = 0;
	p->world.col = 0;
	p->world.row = 0;
	p->world.map = malloc(sizeof(int *) * (p->world.max_row + 1));
	while (col < p->world.max_row)
	{
		p->world.map[col] = malloc(sizeof(int) * (p->world.max_col));
		row = 0;
		while (row < p->world.max_col)
		{
			p->world.map[col][row] = 'A';
			row++;
			if (row == p->world.max_col)
				p->world.map[col][row] = '\0';
		}
		col++;
	}
}

void	parse_map(t_param *p, char **map_array)
{
	p->world.max_row = count_col(p, map_array);
	p->world.max_col = count_row(map_array);
	printf("max row is %i\n", p->world.max_row);
	printf("max col is %i\n", p->world.max_col);
	map_init(p);
	create_map(map_array, p);
	define_position(p);
	printf("player position now is x = %f y = %f\n", p->pl.x_pos, p->pl.y_pos);
//	check_map(p, p->pl.x_pos, p->pl.y_pos);
}

void	set_texture_path(t_param *p, char *xpm, char **texture)
{
	int		fd;

	fd = open(xpm, O_RDONLY);
	if (fd < 0)
		error_handling(TXT_INPUT, p);
	close(fd);
	*texture = xpm;
	printf("texture path now is %s\n", *texture);
}

void	set_texture(t_param *p, char *line, char **texture, int *i)
{
	int		j;
	char	*path;

	(*i) = (*i) + 2;
	if (*texture != NULL)
		error_handling(TXT_DOUBLE, p);
	while (line[*i] == ' ')
		(*i)++;
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	path = malloc(sizeof(char) * (*i - j + 1));
	if (!path)
		error_handling(XPM_MALLOC, p);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
	{
		path[j] = line[*i];
		j++;
		(*i)++;
	}
	path[j] = '\0';
	set_texture_path(p, path, texture);
}

void	convert_color(int r, int g, int b, unsigned int *color)
{
	unsigned int	result;

	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	*color = result;
}

void	check_color_input(char *line, t_param *p)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!(line[j] == 'F' || line[j] == 'C' || line[j] == ' '
				|| line[j] == ',' || (line[j] >= '0' && line[j] <= '9')))
			error_handling(RGB_STRING, p);
		j++;
	}
}

void	set_color(t_param *p, char *line, unsigned int *color, int *i)
{
	int	red;
	int	green;
	int	blue;

	if (line[*i] == 'F' && p->text.floor != 0)
		error_handling(COLOR_DOUBLE, p);
	if (line[*i] == 'C' && p->text.ceiling != 0)
		error_handling(COLOR_DOUBLE, p);
	check_color_input(line, p);
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	red = my_atoi(line, i);
	(*i)++;
	green = my_atoi(line, i);
	(*i)++;
	blue = my_atoi(line, i);
	while (line[*i] == ' ')
		(*i)++;
	if (red > 255 || green > 255 || blue > 255 || line[*i] != '\0')
		error_handling(COLOR_INPUT, p);
	convert_color(red, green, blue, color);
	printf("color is now %x\n", *color);
}

void	check_resolution_input(char *line, t_param *p)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!(line[j] == 'R' || line[j] == ' '
				|| (line[j] >= '0' && line[j] <= '9')))
			error_handling(RES_INVALID, p);
		j++;
	}
}

void	get_resolution(t_param *p, char *line, int *i)
{
	if (p->win.res_check)
		error_handling(RES_DOUBLE, p);
	p->win.res_check = 1;
	check_resolution_input(line, p);
	(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	p->win.x = my_atoi(line, i);
	p->win.y = my_atoi(line, i);
	if (p->win.x <= 0 || p->win.y <= 0)
		error_handling(RES_INVALID, p);
	printf("width is %i, heigth is %i\n", p->win.x, p->win.y);
	if (p->win.x > 1440)
		p->win.x = 1440;
	if (p->win.y > 2560)
		p->win.y = 2560;
}

int	check_param(char *line, t_param *p)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(p, line, &i);
	if (line[i] == 'F' && line[i + 1] == ' ')
		set_color(p, line, &p->text.floor, &i);
	if (line[i] == 'C' && line[i + 1] == ' ')
		set_color(p, line, &p->text.ceiling, &i);
	if (line[i] == '1' || line[i] == '0' || line[i] == '2')
		return (0);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.n_txt, &i);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.e_txt, &i);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.s_txt, &i);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.w_txt, &i);
	if (line[i] == 'S' && line[i + 1] == ' ')
		set_texture(p, line, &p->text.sp_txt, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(p, line, &i);
	return (1);
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

char	**get_lines(char **lines, char **tmp, int fd)
{
	char	*s;
	int		i;
	int		j;
	int		ret;

	ret = 1;
	i = 1;
	while (ret)
	{
		ret = get_next_line(fd, &s);
		tmp = lines;
		j = 0;
		lines = malloc((i + 1) * sizeof(char *));
		copier(lines, &j, tmp);
		free(tmp);
		lines[j] = s;
		j++;
		lines[j] = 0;
		i++;
	}
	return (lines);
}

char	**parse_lines(t_param *p, char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == '\n')
			j++;
		if (!check_param(lines[i], p))
			return (&lines[i]);
		i++;
	}
	error_handling(MAP_INVALID, p);
	return (lines);
}

int	parsing(t_param *p, char *file)
{
	int		fd;
	char	**array;
	char	**map_array;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handling(FD, p);
	array = NULL;
	p->lines = 0;
	p->lines = get_lines(p->lines, array, fd);
	close (fd);
	map_array = parse_lines(p, p->lines);
	check_input(p);
	parse_map(p, map_array);
	p->sprites.spr = parse_sprites(p);
//	printf("sprite location %f, %f\n", p->sprites->spr.x, p->sprites->spr.y);
	return (1);
}

void	init_screen(t_param *p)
{
//	p->img.ptr = mlx_new_image(p->mlx.ptr, p->win.x, p->win.y);
//	p->img.addr = (int *)mlx_get_data_addr(p->img.ptr, &p->img.bpp,
//			&p->img.s_len, &p->img.endian);
}

void	img_to_win(t_param *p)
{
	init_screen(p);
	fill(p);
//	mlx_put_image_to_window(p->mlx.ptr, p->win.ptr, p->img.ptr, 10, 10);
	free(p->img.ptr);
	free(p->img.addr);
}

int 	update(t_param *p)
{
	img_to_win(p);
	return (0);
}

void	start_point(t_param p, char *file)
{
	printf("\nthis is START POINT\n");
//	p.mlx.ptr = mlx_init();
	if (parsing(&p, file) == -1)
		close_game(&p);
//	p.win.ptr = mlx_new_window(p.mlx.ptr, p.win.x, p.win.y, "cub3d");
	img_to_win(&p);
//	mlx_hook(p.win.ptr, 2, 0, key_check, &p);
//	mlx_hook(p.win.ptr, 17, 0, close_game, &p);
//	mlx_loop_hook(p.mlx.ptr, update, &p);
//	mlx_loop(p.mlx.ptr);
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && cub_check(argv[1]))
		init_param(argv[1]);
	else
		printf("ERROR:\nArguments invalid.\n");
	return (0);
}