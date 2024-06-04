/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:51:03 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:29 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	minimap_init(t_mdata *data)
{
	data->minimap.img = mlx_new_image(data->main_data.mlx_ptr, 200, 100);
	data->minimap.addr = (int *)mlx_get_data_addr(data->minimap.img, \
	&data->minimap.bits_per_pixel, &data->minimap.line_length, \
	&data->minimap.endian);
}

void	minimap_draw(t_mdata *data, int player_x, int player_y)
{
	int	x;
	int	y;
	int	original_x;
	int	original_y;

	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y++ < 200)
		{
			original_x = (int)(x * (double)data->rows / 100.0);
			original_y = (int)(y * (double)data->columns / 200.0);
			if (original_x == player_x && original_y == player_y)
				data->minimap.addr[x * 200 + y] = 0xFF0000;
			else
			{
				if (data->map[original_x][original_y] == 1)
					data->minimap.addr[x * 200 + y] = 0x000000;
				else if (data->map[original_x][original_y] == 0)
					data->minimap.addr[x * 200 + y] = 0xFFFFFF;
			}
		}
		x++;
	}
}

void	init_image(t_mdata *data)
{
	data->textures[0].img = 0;
	data->textures[1].img = 0;
	data->textures[2].img = 0;
	data->textures[3].img = 0;
	data->minimap.img = 0;
	data->main_data.img = 0;
	data->main_data.mlx_win = 0;
	data->minimap.img = 0;
}
