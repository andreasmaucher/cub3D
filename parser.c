#include "cub3D.h"

void	parser(char *file_name, t_mdata *data)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(file_name, O_RDONLY);
	//open_check(file_name, data);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, data);
		floor_ceiling(str, data);
		textures(str, data);
		map_check(str, data);
		free(str);
	}
	close(fd);
	/* printf("no: %s\nso: %s\nea: %s\nwe: %s\nc: %d\nf: %d\nrows: %d\ncolumns: %d\nstart_x: %d\nstart_y: %d\n" \
	, data->no, data->so, data->ea, data->we, data->c, data->f, data->rows, data->columns, data->start_x, data->start_y); */
	if (data->columns == 0 || data->rows == 0)
		error_handle(data, "there is no map\n");
	create_map(file_name, data);
	//print_map(data);
}

int	color_finder(char *str, t_mdata *data)
{
	int	ret;
	int	rgb;

	ret = 0;
	rgb = 0;
	if (color_check(str) == 1)
		data->err_msg = "invalid color\n";
	while (str[data->i] != '\0')
	{
		if (str[data->i] >= '0' && str[data->i] <= '9')
		{
			ret = (ret * 10) + (str[data->i] - '0');
			if (ret > 255 || ret < 0)
				data->err_msg = "invalid color code\n";;
		}
		else if (str[data->i] == ',')
		{
			rgb = (rgb << 8) | (ret & 0xFF);
			ret = 0;
		}
		data->i++;
	}
	rgb = (rgb << 8) | (ret & 0xFF);
	return (rgb);
}

void	floor_ceiling(char *str, t_mdata *data)
{
	char *temp;

	temp = str;
	data->i = 0;
	while (*temp == ' ')
		temp++;
	if (temp[0] == 'F')
		data->f = color_finder(temp, data);
	else if (temp[0] == 'C')
		data->c = color_finder(temp, data);
}

void	error_handle(t_mdata *data, char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	(void)data;
	exit(0);
}

int	color_check(char *str)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && str[i] != ' ')
			return (1);
		if (str[i] == ',')
			counter++;
		if (counter > 2)
			return (1);
		i++;
	}
	return (0);
}

int	open_check(char *file_name, t_mdata *data)
{
	if (open(file_name, O_RDONLY) == -1)
		data->err_msg = "open problem\n";
	return (0);
}

int	texture_extractor(char *str, char *texture, t_mdata *data)
{
	int	i;

	i = 2;
	if (texture[0] != '\0')
	{
		data->err_msg = "more than one texture for a side\n";;
		return (0);
	}
	while (str[i] == ' ')
		i++;
	if (str[i] == '.'|| str[i] == '/')
	{
		strncpy(texture, &str[i], MAX_PATH - 1);//change with ft_ version
		texture[MAX_PATH - 1] = '\0';
	}
	else
		data->err_msg = "invalid texture\n";;
	return (0);
}

void	textures(char *s, t_mdata *data)
{
	int		i;
	char	*str;

	i = 0;
	str = s;
	data->i = 0;
	while (*str == ' ')
		str++;
	if (str[i] == 'S' && str[i + 1] && str[i + 1] == 'O')
		texture_extractor(str, data->so, data);
	else if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O')
		texture_extractor(str, data->no, data);
	else if (str[i] == 'E' && str[i + 1] && str[i + 1] == 'A')
		texture_extractor(str, data->ea, data);
	else if (str[i] == 'W' && str[i + 1] && str[i + 1] == 'E')
		texture_extractor(str, data->we, data);
	else if (str[i] != '\n' && str[i] != '\0' && str[i] != 'C' \
	&& str[i] != 'F' && str[i] != 'N' && str[i] != 'S' && str[i] != 'E' \
	&& str[i] != 'W' && str[i] != '1' && str[i] != '0')
		data->err_msg = "invalid character in file\n";
}

void	map_check(char *str, t_mdata *data)
{
	if (is_map(str, data) == 1)
	{
		if (data->f == -1 || data->c == -1 || data->no[0] == '\0' \
		|| data->so[0] == '\0' || data->we[0] == '\0' || data->ea[0] == '\0')
			data->err_msg = "full color/texture data not present\n";;
		if (ft_strlen(str) > data->columns)
			data->columns = ft_strlen(str);
		data->rows = data->rows + 1;
	}
}

int		is_map(char *str, t_mdata *data)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '0' || str[i] == '1')
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E' \
			&& str[i] != 'W' && str[i] != '\n')
			{
				data->err_msg = "invalid character in map\n";
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int		create_map(char *file_name, t_mdata *data)
{
	int			fd;
	int			ret;
	char		*str;
	int			i;

	i = 0;
	ret = 1;
	str = NULL;
	fd = open(file_name, O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, data);
		if (is_map(str, data) == 1)
		{
			if (wall_check(data, str, i) != 1)
				copy_map(str, data);
			else
				data->err_msg = "walls are open\n";;
			i++;
		}
		free(str);
	}
	close(fd);
	//print_map(data);
	ray_init(data);
	mlx_main(data);
	return (0);
}

int		copy_map(char *str, t_mdata *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (start_point(str[i], data, data->x, i) == 1)
			data->map[data->x][i] = 0;
		else if (str[i] == ' ')
			data->map[data->x][i] = space_sub(data, str[i - 1], i, ft_strlen(str));
		else
			data->map[data->x][i] = str[i] - '0';
		i++;
	}
	while (i <= data->columns)
	{
		data->map[data->x][i] = 1;
		i++;
	}
	data->x++;
	return (0);
}

int		start_point(char c, t_mdata *data, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->start != '\0')
			data->err_msg = "multiple starting points\n";
		data->start = c;
		data->start_x = i;
		data->start_y = j;
		return (1);
	}
	return (0);
}

int	space_sub(t_mdata *data, char c, int i, int size)
{
	if (data->x == 0 || data->x == data->rows)
		return (1);
	else if (i == 0 || i == size)
		return (1);
	else if (c == '1')
		return (0);
	else
		return (0);
}

void	print_map(t_mdata *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%d:", i + 1);
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			printf("%d ", data->map[i][j]);
			j++;
		}
		i++;
		printf("\n%d:", i + 1);
	}
}

int	wall_check(t_mdata *data, char *str, int row)
{
	int i;

	i = 0;
	if (str[0] != '1')
		return (1);
	if (str[ft_strlen(str) - 1] != '1')
		return (1);
	if (row == 0 || row == data->rows)
	{
		while (str[i] != '\0')
		{
			if (str[i] != '1')
				return (1);
			i++;
		}
	}
	return (0);
}
