/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:55:12 by amaucher          #+#    #+#             */
/*   Updated: 2024/06/05 01:07:43 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
sets the floor and ceiling colors;
it loops for pixels below and above the wall;
*/
void	color_ceiling_and_floor(t_mdata *data)
{
	int	j;

	j = -1;
	data->ray.drawend = data->wy - data->ray.drawstart;
	while (++j < data->ray.drawstart)
	{
		data->main_data.addr[j * data->main_data.line_length / 4
			+ data->ray.x] = data->c;
	}
	j = data->ray.drawend;
	while (++j < data->wy)
	{
		data->main_data.addr[j * data->main_data.line_length / 4
			+ data->ray.x] = data->f;
	}
}

/*
determines the wall side
*/
int	calculate_direction(t_mdata *data)
{
	int	direction;

	if (data->ray.side == 0 && data->ray.raydirx < 0)
		direction = SOUTH;
	if (data->ray.side == 0 && data->ray.raydirx >= 0)
		direction = NORTH;
	if (data->ray.side == 1 && data->ray.raydiry < 0)
		direction = EAST;
	if (data->ray.side == 1 && data->ray.raydiry >= 0)
		direction = WEST;
	return (direction);
}

/*
first: calculates the intersection point of the ray with the wall;
floor function used to normalize the value to the range[0, 1];
last: calculates the texture x coordinate of the intersection point;
*/
int	calculate_hit_point(t_mdata *data)
{
	double	wall_x_hit;
	int		tex_x_hit;

	if (data->ray.side == 0)
		wall_x_hit = data->ray.posy + data->ray.perpwalldist
			* data->ray.raydiry;
	else
		wall_x_hit = data->ray.posx + data->ray.perpwalldist
			* data->ray.raydirx;
	wall_x_hit -= floor(wall_x_hit);
	tex_x_hit = (int)(wall_x_hit * (double)TEX_WIDTH);
	if (data->ray.side == 0 && data->ray.raydirx > 0)
		tex_x_hit = TEX_WIDTH - tex_x_hit - 1;
	if (data->ray.side == 1 && data->ray.raydiry < 0)
		tex_x_hit = TEX_WIDTH - tex_x_hit - 1;
	return (tex_x_hit);
}

/*
this loop colors all pixels of the wall in bufx and the display window (addr);
1. starting texture position is calculated (tex_pos)
2. calculate current texture y-coordinate (tex_y)
3. get color based on the direction and texture coordinates;
4. store color in bufx and data.addr
5. make color darker for y-sides: R, G and B byte each divided through two 
with a "shift" and an "and"
*/
void	colouring_loop(t_mdata *data, int tex_x_hit)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		direction;

	data->color = 0;
	step = 1.0 * TEX_HEIGHT / data->ray.lineheight;
	tex_pos = (data->ray.drawstart - data->wy / 2 + data->ray.lineheight / 2)
		* step;
	y = data->ray.drawstart;
	while (y < data->ray.drawend)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		direction = calculate_direction(data);
		data->color = data->textures[direction].addr[TEX_HEIGHT * tex_y + 
			tex_x_hit];
		data->main_data.addr[y * data->main_data.line_length / 4
			+ data->ray.x] = data->color;
		if (data->ray.side == 1)
			data->color = (data->color >> 1) & 8355711;
		y++;
	}
}

int	drawing_function(t_mdata *data)
{
	int		tex_x_hit;

	color_ceiling_and_floor(data);
	tex_x_hit = calculate_hit_point(data);
	colouring_loop(data, tex_x_hit);
	return (0);
}
