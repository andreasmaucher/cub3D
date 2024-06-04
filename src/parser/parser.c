/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:54 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:12:00 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	parser(char *file_name, t_mdata *data)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(file_name, O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, data);
		floor_ceiling(str, data);
		textures(str, data);
		map_check(str, data);
		free(str);
	}
	close(fd);
	if (data->columns == 0 || data->rows == 0)
		error_handle(data, "there is no map\n");
	create_map(file_name, data);
}

void	error_handle(t_mdata *data, char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	if (data->clean_exit == 1)
		clean_exit(data);
	exit(0);
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
		data->err_msg = "more than one texture for a side\n";
		return (0);
	}
	while (str[i] == ' ')
		i++;
	if (str[i] == '.' || str[i] == '/')
	{
		strncpy(texture, &str[i], MAX_PATH - 1);
		texture[MAX_PATH - 1] = '\0';
	}
	else
		data->err_msg = "invalid texture\n";
	return (0);
}

void	map_check(char *str, t_mdata *data)
{
	if (is_map(str, data) == 1)
	{
		if (data->newline == 1)
			data->err_msg = "empty line in map\n";
		if (data->f == -1 || data->c == -1 || data->no[0] == '\0' \
		|| data->so[0] == '\0' || data->we[0] == '\0' || data->ea[0] == '\0')
		{
			data->err_msg = "full color/texture data not present\n";
			return ;
		}
		if (ft_strlen(str) > data->columns)
			data->columns = ft_strlen(str);
		data->rows = data->rows + 1;
		data->inmap = 1;
	}
	else if (is_map(str, data) == 0 && data->inmap == 1)
		data->newline = 1;
}
