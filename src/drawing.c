/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:31:37 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:35 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	drawing_loop(t_mdata *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltadistx;
			data->ray.mapx += data->ray.stepx;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sidedisty += data->ray.deltadisty;
			data->ray.mapy += data->ray.stepy;
			data->ray.side = 1;
		}
		if (data->map[data->ray.mapx][data->ray.mapy] == 1)
			data->ray.hit = 1;
	}
	drawing_cal(data);
}

void	drawing_cal(t_mdata *data)
{
	if (data->ray.side == 0)
		data->ray.perpwalldist = fabs(data->ray.sidedistx - \
		data->ray.deltadistx);
	else
		data->ray.perpwalldist = fabs(data->ray.sidedisty - \
		data->ray.deltadisty);
	data->ray.lineheight = (int)(data->wy / data->ray.perpwalldist);
	data->ray.drawstart = -data->ray.lineheight / 2 + data->wy / 2;
	if (data->ray.drawstart < 0)
		data->ray.drawstart = 0;
	else
		data->ray.drawstart = data->ray.drawstart;
	data->ray.drawend = data->ray.lineheight / 2 + data->wy / 2;
	if (data->ray.drawend >= data->wy || data->ray.drawend < 0)
		data->ray.drawend = data->wy - 1;
	else
		data->ray.drawend = data->ray.drawend;
}

int	raycasting(t_mdata *data)
{
	data->ray.x = 0;
	while (data->ray.x < data->wx)
	{
		dda_calculation(data);
		step_sidedist(data);
		drawing_function(data);
		data->ray.x++;
	}
	minimap_draw(data, (int)round(data->ray.posx), (int)round(data->ray.posy));
	mlx_put_image_to_window(data->main_data.mlx_ptr, data->main_data.mlx_win,
		data->main_data.img, 0, 0);
	if (data->mini == 1)
		mlx_put_image_to_window(data->main_data.mlx_ptr, \
		data->main_data.mlx_win, data->minimap.img, 0, 0);
	move_forward_back(data);
	move_left_right(data);
	rotate_right_left(data);
	return (0);
}

void	screen_size(t_mdata *data)
{
	mlx_get_screen_size(data->main_data.mlx_ptr, &data->screenx, \
	&data->screeny);
	if (data->wx > data->screenx)
		data->wx = data->screenx;
	if (data->wy > data->screeny)
		data->wy = data->screeny;
}
