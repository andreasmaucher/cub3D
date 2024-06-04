/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:31:56 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:12:09 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	gnl_exit(char **buff, t_mdata *data)
{
	if (data->err_msg != NULL && *buff)
	{
		free(*buff);
		error_handle(data, data->err_msg);
	}
	return (0);
}

int	check_buff(char **buff, char **line)
{
	int	ret;

	ret = 1;
	if (*buff)
		ret = ft_copy(line, buff);
	return (ret);
}

int	allocate_buff(char **buff)
{
	if (!*buff)
	{
		*buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!*buff)
			return (-1);
	}
	return (1);
}

int	read_file(int fd, char **buff, char **line)
{
	int	ret;

	ret = read(fd, *buff, BUFFER_SIZE);
	while (ret > 0)
	{
		(*buff)[ret] = '\0';
		if (!ft_copy(line, buff))
			return (1);
		ret = read(fd, *buff, BUFFER_SIZE);
	}
	return (ret);
}

int	get_next_line(int fd, char **line, t_mdata *data)
{
	static char	*buff = NULL;
	int			ret;

	if (gnl_exit(&buff, data) == 1)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	ret = check_buff(&buff, line);
	if (ret == 0)
		return (1);
	if (allocate_buff(&buff) == -1)
		return (-1);
	ret = read_file(fd, &buff, line);
	if (ret <= 0)
		return (ft_eof(ret, &buff, line));
	return (1);
}
