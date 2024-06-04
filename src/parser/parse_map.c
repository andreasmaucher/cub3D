/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:47 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:11:58 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	wall_check(t_mdata *data, char *str, int row)
{
	int	i;

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

int	copy_map(char *str, t_mdata *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (start_point(str[i], data, data->x, i) == 1)
			data->map[data->x][i] = 0;
		else if (str[i] == ' ')
			data->map[data->x][i] = space_sub(data, str[i - 1], i, \
			ft_strlen(str));
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

int	create_map(char *file_name, t_mdata *data)
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
				data->err_msg = "walls are open\n";
			i++;
		}
		free(str);
	}
	close(fd);
	mlx_main(data);
	return (0);
}

int	is_map(char *str, t_mdata *data)
{
	int	i;

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
