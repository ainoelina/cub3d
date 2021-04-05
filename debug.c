#include "./srcs/cub3d.h"
#include "./mlx/mlx.h"

void	error_handling(int error, t_param *p)
{
	if (error == FD)
		printf("ERROR:\nCould not open file.\n");
	if (error == COLOR_INPUT)
		printf("ERROR:\nWrong color input for floor/ceiling.\n");
	if (error == RGB_STRING)
		printf("ERROR:\nIncorrect floor/ceiling input.\n");
	if (error == TXT_DOUBLE)
		printf("ERROR:\nTexture set twice.\n");
	if (error == XPM_MALLOC)
		printf("ERROR:\nMallocing for .xpm file failed.\n");
	if (error == MAP_MALLOC)
		printf("ERROR:\nMallocing for map failed.\n");
	if (error == MAP_INVALID)
		printf("ERROR:\nInvalid map input.\n");
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

int	map_counter(t_param *p, char *line)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
			|| line[i] == 'W')
			counter++;
		i++;
	}
	if (p->map.x != 0 && p->map.x != counter)
		return (-1);
	return (counter);
}

char	*copy_map_contents(t_param *p, int *i, char *line, char *map)
{
	int	k;

	k = 0;
	while (line[*i])
	{
		if (line[*i] == '1' || line[*i] == '0' || line[*i] == 'N'
			|| line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W')
		{
			map[k] = line[*i];
			k++;
		}
		else if (line[*i] == '2')
		{
			map[k] = line[*i];
			k++;
			p->map.sprite++;
		}
		else if (line[*i] != ' ')
			return (NULL);
		(*i)++;
	}
	map[k] = '\0';
	return (map);
}

char	*define_map(t_param *p, char *line, int *i)
{
	char	*map;
	int k;

	k = 0;
	map = malloc(sizeof(char) * (map_counter(p, line) + 1));
	if (!map)
		return (NULL);
	map = copy_map_contents(p, i, line, map);
/*	while (line[*i])
	{
		if (line[*i] == '1' || line[*i] == '0' || line[*i] == 'N'
			|| line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W')
		{
			map[k] = line[*i];
			k++;
		}
		else if (line[*i] == '2')
		{
			map[k] = line[*i];
			k++;
			p->map.sprite++;
		}
		else if (line[*i] != ' ')
			return (NULL);
		(*i)++;
	}
*/
	if (map == NULL)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	parse_map(t_param *p, char *line, int *i)
{
	char	**temp;
	int		j;

	temp = malloc(sizeof(char *) * (p->map.y + 2));
	if (!temp)
		error_handling(MAP_MALLOC, p);
	printf("map.y is now %i\n", p->map.y);
	j = 0;
	while (j < p->map.y)
	{
		temp[j] = p->map.map[j];
		j++;
	}
	temp[p->map.y] = define_map(p, line, i);
	if (temp[p->map.y] == NULL)
	{
		free(temp);
		error_handling(MAP_INVALID, p);
	}
	temp[p->map.y + 1] = NULL;
	if (p->map.y > 0)
		free(p->map.map);
	p->map.map = temp;
	int u = 0;
	int y = 0;
	while (u < 6)
	{
		while(y < 5)
		{
			printf("%c", p->map.map[y][u]);
			y++;
		}
		u++;
	}
	p->map.y++;
	return (0);
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

int	key_check(int key, void *arg)
{
	printf("\nchecking the KEY\n");
	if (key == 53)
		close_game(arg);
	return (1);
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

void	set_texture_path(t_param *p, char *xpm, char **texture)
{
	int		fd;

	fd = open(xpm, O_RDONLY);
	if (fd < 0)
		error_handling(TXT_INPUT, p);
	close(fd);
	*texture = xpm;
	printf("direction texture now is %s\n", *texture);
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

/*
int	color_input(int *i, char *line)
{
	while(line[*i] == ' ')
		(*i)++;
	(*i)++;
	if (line[*i] != ',')
		error_handling(RGB_STRING);
	return (0);
}
*/

void	set_color(t_param *p, char *line, unsigned int *color, int *i)
{
	int	red;
	int	green;
	int	blue;

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
}

void	get_resolution(t_param *p, char *line, int *i)
{
	(*i)++;
	p->win.x = my_atoi(line, i);
	p->win.y = my_atoi(line, i);
	printf("width is %i, heigth is %i\n", p->win.x, p->win.y);
	while (line[*i] == ' ')
		i++;
}

int	check_line(t_param *p, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		parse_map(p, line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.n_txt, &i);
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.e_txt, &i);
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.s_txt, &i);
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		set_texture(p, line, &p->text.w_txt, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		get_resolution(p, line, &i);
	if (line[i] == 'F' && line[i + 1] == ' ')
		set_color(p, line, &p->text.floor, &i);
	if (line[i] == 'C' && line[i + 1] == ' ')
		set_color(p, line, &p->text.ceiling, &i);
	return (0);
}

int	parser(t_param *p, char *file)
{
	char	*line;
	int		fd;
	int		reader;

	printf("\naccessing parse funcion\n\n");
	fd = open(file, O_RDONLY);
	reader = 1;
	if (fd == -1)
		error_handling(FD, p);
	while (reader == 1)
	{
		reader = get_next_line(fd, &line);
		if (check_line(p, line) == -1)
			reader = -1;
		free(line);
	}
	printf("floor color is now %x\n", p->text.floor);
	printf("ceiling color is now %x\n", p->text.ceiling);
	printf("n texture path is %s\n", p->text.n_txt);
	printf("e texture path is %s\n", p->text.e_txt);
	printf("s texture path is %s\n", p->text.s_txt);
	printf("w texture path is %s\n", p->text.w_txt);
	close(fd);
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
}

void	init_param(char *file)
{
	t_param	p;
	t_mlx	mlx;
	t_img	img;
	t_win	win;
	t_text	text;
	t_map	map;

	p.err = 0;
	mlx.ptr = NULL;
	img.ptr = NULL;
	img.addr = NULL;
	win.ptr = NULL;
	win.x = 0;
	win.y = 0;
	map.y = 0;
	map.x = 0;
	map.map = NULL;
	map.sprite = 0;
	init_textures(&text);
	p.map = map;
	p.mlx = mlx;
	p.img = img;
	p.win = win;
	p.text = text;
	start_point(p, file);
}

void	init_screen(t_param *p)
{
	printf("\nhere i initialise SCREEN\n");
//	p->img.ptr = mlx_new_image(p->mlx.ptr, p->win.x, p->win.y);
//	p->img.addr = (int *)mlx_get_data_addr(p->img.ptr, &p->img.bpp,
//			&p->img.s_len, &p->img.endian);
}

void	img_to_win(t_param *p)
{
	printf("\nputting IMG to SCREEN\n");
	init_screen(p);
	printf("do i ever get here\n");
//	mlx_put_image_to_window(p->mlx.ptr, p->win.ptr, p->img.ptr, 0, 0);
	free(p->img.ptr);
	free(p->img.addr);
}

void	start_point(t_param p, char *file)
{
	printf("\nthis is START POINT\n");
//	p.mlx.ptr = mlx_init();
	if (parser(&p, file) == -1)
		close_game(&p);
//	p.win.ptr = mlx_new_window(p.mlx.ptr, p.win.x, p.win.y, "cub3d");
	img_to_win(&p);
//	mlx_hook(p.win.ptr, 2, 0, key_check, &p);
//	mlx_hook(p.win.ptr, 17, 0, close_game, &p);
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
