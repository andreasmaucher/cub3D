/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:02 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:33 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keycode, t_mdata *data)
{
	if (keycode == 119)
		data->main_data.forward = 1;
	else if (keycode == 115)
		data->main_data.back = 1;
	else if (keycode == 97)
		data->main_data.left = 1;
	else if (keycode == 100)
		data->main_data.right = 1;
	else if (keycode == 65361)
		data->main_data.rotate_left = 1;
	else if (keycode == 65363)
		data->main_data.rotate_right = 1;
	else if (keycode == 109)
		data->mini = data->mini * -1;
	else if (keycode == 111)
	{
		data->wx = data->wx + 10;
		data->wy = data->wy + 10;
		change_win(data);
		return (mlx_main(data));
	}
	else if (keycode == 65307)
		clean_exit(data);
	return (1);
}

int	key_release(int keycode, t_mdata *data)
{
	if (keycode == 119)
		data->main_data.forward = 0;
	else if (keycode == 115)
		data->main_data.back = 0;
	else if (keycode == 97)
		data->main_data.left = 0;
	else if (keycode == 100)
		data->main_data.right = 0;
	else if (keycode == 65361)
		data->main_data.rotate_left = 0;
	else if (keycode == 65363)
		data->main_data.rotate_right = 0;
	return (1);
}

int	clean_exit(t_mdata *data)
{
	if (data->textures[0].img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->textures[0].img);
	if (data->textures[1].img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->textures[1].img);
	if (data->textures[2].img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->textures[2].img);
	if (data->textures[3].img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->textures[3].img);
	if (data->minimap.img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->minimap.img);
	if (data->main_data.img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->main_data.img);
	if (data->main_data.mlx_win)
		mlx_destroy_window(data->main_data.mlx_ptr, data->main_data.mlx_win);
	mlx_destroy_display(data->main_data.mlx_ptr);
	free(data->main_data.mlx_ptr);
	exit(0);
	return (0);
}

int	change_win(t_mdata *data)
{
	if (data->main_data.img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->main_data.img);
	if (data->main_data.mlx_win)
		mlx_destroy_window(data->main_data.mlx_ptr, data->main_data.mlx_win);
	mlx_destroy_display(data->main_data.mlx_ptr);
	free(data->main_data.mlx_ptr);
	return (0);
}
