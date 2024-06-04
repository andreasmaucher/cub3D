/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:33 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:27 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_forward_back(t_mdata *data)
{
	if (data->main_data.forward == 1)
	{
		if (data->map[(int)(data->ray.posx + (data->ray.dirx * data-> \
		ray.movespeed * 2))][(int)data->ray.posy] == 0)
			data->ray.posx += data->ray.dirx * data->ray.movespeed;
		if (data->map[(int)(data->ray.posx)][(int)(data->ray.posy + \
		(data->ray.diry * data->ray.movespeed * 2))] == 0)
			data->ray.posy += data->ray.diry * data->ray.movespeed;
	}
	if (data->main_data.back == 1)
	{
		if (data->map[(int)(data->ray.posx - (data->ray.dirx * data-> \
		ray.movespeed * 2))][(int)(data->ray.posy)] == 0)
			data->ray.posx -= data->ray.dirx * data->ray.movespeed;
		if (data->map[(int)(data->ray.posx)][(int)(data->ray.posy -
					(data->ray.diry * data->ray.movespeed * 2))] == 0)
			data->ray.posy -= data->ray.diry * data->ray.movespeed;
	}
}

void	move_left_right(t_mdata *data)
{
	if (data->main_data.right == 1)
	{
		if (data->map[(int)(data->ray.posx + data->ray.diry * \
		(data->ray.movespeed * 2))][(int)data->ray.posy] == 0)
			data->ray.posx += data->ray.diry * data->ray.movespeed;
		if (data->map[(int)data->ray.posx][(int)(data->ray.posy - \
		data->ray.dirx * (data->ray.movespeed * 2))] == 0)
			data->ray.posy -= data->ray.dirx * data->ray.movespeed;
	}
	if (data->main_data.left == 1)
	{
		if (data->map[(int)(data->ray.posx - data->ray.diry * \
		(data->ray.movespeed * 2))][(int)data->ray.posy] == 0)
			data->ray.posx -= data->ray.diry * data->ray.movespeed;
		if (data->map[(int)data->ray.posx][(int)(data->ray.posy + \
		data->ray.dirx * (data->ray.movespeed * 2))] == 0)
			data->ray.posy += data->ray.dirx * data->ray.movespeed;
	}
}

void	rotate_right_left(t_mdata *data)
{
	double	oldplanx;
	double	olddirx;

	oldplanx = 0;
	olddirx = 0;
	oldplanx = data->ray.planx;
	olddirx = data->ray.dirx;
	if (data->main_data.rotate_right == 1)
	{
		data->ray.dirx = data->ray.dirx * cos(-data->ray.rotspeed) - \
		data->ray.diry * sin(-data->ray.rotspeed);
		data->ray.diry = olddirx * sin(-data->ray.rotspeed) + \
		data->ray.diry * cos(-data->ray.rotspeed);
		data->ray.planx = data->ray.planx * cos(-data->ray.rotspeed) \
		- data->ray.plany * sin(-data->ray.rotspeed);
		data->ray.plany = oldplanx * sin(-data->ray.rotspeed) + \
		data->ray.plany * cos(-data->ray.rotspeed);
	}
	rotate_left(data, olddirx);
}

void	rotate_left(t_mdata *data, double olddirx)
{
	double	oldplanx;

	oldplanx = 0;
	if (data->main_data.rotate_left == 1)
	{
		olddirx = data->ray.dirx;
		oldplanx = data->ray.planx;
		data->ray.dirx = data->ray.dirx * cos(data->ray.rotspeed) - \
		data->ray.diry * sin(data->ray.rotspeed);
		data->ray.diry = olddirx * sin(data->ray.rotspeed) + data-> \
		ray.diry * cos(data->ray.rotspeed);
		data->ray.planx = data->ray.planx * cos(data->ray.rotspeed) - \
		data->ray.plany * sin(data->ray.rotspeed);
		data->ray.plany = oldplanx * sin(data->ray.rotspeed) + \
		data->ray.plany * cos(data->ray.rotspeed);
	}
}

int	mouse_move(int x, int y, t_mdata *data)
{
	int		delta_x;

	if (data->mini == -1)
		return (0);
	if (data->main_data.last_x == -1 && data->main_data.last_y == -1)
	{
		data->main_data.last_x = x;
		data->main_data.last_y = y;
		return (0);
	}
	delta_x = x - data->main_data.last_x;
	data->main_data.last_x = x;
	data->main_data.last_y = y;
	if (delta_x > 0)
		data->main_data.rotate_right = 1;
	else if (delta_x < 0)
		data->main_data.rotate_left = 1;
	else
	{
		data->main_data.rotate_right = 0;
		data->main_data.rotate_left = 0;
	}
	return (0);
}
