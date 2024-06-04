/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:41 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:11:47 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	start_point(char c, t_mdata *data, int i, int j)
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
	if (counter != 2)
		return (1);
	return (0);
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
				data->err_msg = "invalid color code\n";
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
	char	*temp;

	temp = str;
	data->i = 0;
	while (*temp == ' ')
		temp++;
	if ((temp[0] == 'F' && data->f != -1) || (temp[0] == 'C' && data->c != -1))
	{
		data->err_msg = "multiple definition of F/C colors";
		return ;
	}
	if (temp[0] == 'F')
		data->f = color_finder(temp, data);
	else if (temp[0] == 'C')
		data->c = color_finder(temp, data);
}
