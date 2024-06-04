/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:31:31 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:37 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ray_init(t_mdata *data)
{
	if (data->start == '\0')
		error_handle(data, "no starting point\n");
	data->ray.posx = (double)data->start_x + 0.5;
	data->ray.posy = (double)data->start_y + 0.5;
	data->ray.dirx = 0;
	data->ray.diry = 0;
	data->ray.planx = 0;
	data->ray.plany = 0;
	data->main_data.forward = 0;
	data->main_data.back = 0;
	data->main_data.left = 0;
	data->main_data.right = 0;
	data->main_data.rotate_right = 0;
	data->main_data.rotate_left = 0;
	data->ray.movespeed = 0.01;
	data->ray.rotspeed = 0.0034888889;
	dir_vector_init(data);
}

/* The ratio between the length of the direction and the camera plane 
determinates the FOV, here the direction vector is a bit longer than
the camera plane, so the FOV will be smaller than 90° (more precisely,
the FOV is 2 * atan(0.66/1.0)=66°, which is perfect for a first person
shooter game) */
/*
		0---->y
		|
		|
		↓		↑
		x		->
			↑	N
		  <-W		E->
					↓
				S
				<-
				↓
*/

void	dir_vector_init(t_mdata *data)
{
	if (data->start == 'N')
	{
		data->ray.dirx = -1;
		data->ray.plany = 0.66;
	}
	if (data->start == 'S')
	{
		data->ray.dirx = 1;
		data->ray.plany = -0.66;
	}
	if (data->start == 'E')
	{
		data->ray.diry = 1;
		data->ray.planx = 0.66;
	}
	if (data->start == 'W')
	{
		data->ray.diry = -1;
		data->ray.planx = -0.66;
	}
}

void	dda_calculation(t_mdata *data)
{
	data->ray.hit = 0;
	data->ray.perpwalldist = 0;
	data->ray.camerax = 2 * data->ray.x / (double)data->wx - 1;
	data->ray.raydirx = data->ray.dirx + data->ray.planx * \
						data->ray.camerax;
	data->ray.raydiry = data->ray.diry + data->ray.plany * \
						data->ray.camerax;
	data->ray.mapx = (int)data->ray.posx;
	data->ray.mapy = (int)data->ray.posy;
	if (data->ray.raydirx == 0)
		data->ray.deltadistx = 1e30;
	else
		data->ray.deltadistx = fabs(1 / data->ray.raydirx);
	if (data->ray.raydiry == 0)
		data->ray.deltadisty = 1e30;
	else
		data->ray.deltadisty = fabs(1 / data->ray.raydiry);
}

void	step_sidedist(t_mdata *data)
{
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (data->ray.posx - data->ray.mapx) \
							* data->ray.deltadistx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (data->ray.mapx + 1.0 - data->ray.posx) \
							* data->ray.deltadistx;
	}
	if (data->ray.raydiry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (data->ray.posy - data->ray.mapy) \
							* data->ray.deltadisty;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (data->ray.mapy + 1.0 - data->ray.posy) \
							* data->ray.deltadisty;
	}
	drawing_loop(data);
}
