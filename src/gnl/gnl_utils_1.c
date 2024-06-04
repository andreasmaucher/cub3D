/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:31:44 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:12:05 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	newline_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*temp;

	temp = s1;
	s1 = ft_strjoin(s1, s2);
	free(temp);
	return (s1);
}

void	copy_buff_to_line(char **line, char **buff, int start)
{
	char	*temp;

	temp = ft_substr(*buff, 0, start);
	*line = join_and_free(*line, temp);
	free(temp);
	*buff = ft_subbuff(*buff, start + 1, (ft_strlen(*buff) - start));
}

int	ft_copy(char **line, char **buff)
{
	int	start;

	start = newline_check(*buff);
	if (start >= 0)
	{
		copy_buff_to_line(line, buff, start);
		return (0);
	}
	*line = join_and_free(*line, *buff);
	return (1);
}

int	ft_eof(int ret, char **buff, char **line)
{
	if (ret == -1)
		return (-1);
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}
