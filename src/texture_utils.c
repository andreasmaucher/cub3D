/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:55:12 by amaucher          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:25 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	load_texture(t_mdata *data)
{
	data->clean_exit = 1;
	data->textures[0].img = mlx_xpm_file_to_image(data->main_data.\
	mlx_ptr, data->so, &(data->textures[0].width), &(data->textures[0].height));
	if (!(data->textures[0].img))
		error_handle(data, "Texture SOUTH\n");
	data->textures[1].img = mlx_xpm_file_to_image(data->main_data.\
	mlx_ptr, data->no, &(data->textures[1].width), &(data->textures[1].height));
	if (!(data->textures[1].img))
		error_handle(data, "Texture NORTH\n");
	data->textures[2].img = mlx_xpm_file_to_image(data->main_data.\
	mlx_ptr, data->ea, &(data->textures[2].width), \
	&(data->textures[2].height));
	if (!(data->textures[2].img))
		error_handle(data, "Texture EAST\n");
	data->textures[3].img = mlx_xpm_file_to_image(data->main_data.\
	mlx_ptr, data->we, &(data->textures[3].width), \
	&(data->textures[3].height));
	if (!(data->textures[3].img))
		error_handle(data, "Texture WEST\n");
	get_texture_adress(data);
}

void	get_texture_adress(t_mdata *data)
{
	data->textures[0].addr = (int *)mlx_get_data_addr(data->textures[0].img,
			&data->textures[0].bits_per_pixel,
			&data->textures[0].line_length, &data->textures[0].endian);
	data->textures[1].addr = (int *)mlx_get_data_addr(data->textures[1].img,
			&data->textures[1].bits_per_pixel,
			&data->textures[1].line_length, &data->textures[1].endian);
	data->textures[2].addr = (int *)mlx_get_data_addr(data->textures[2].img,
			&data->textures[2].bits_per_pixel,
			&data->textures[2].line_length, &data->textures[2].endian);
	data->textures[3].addr = (int *)mlx_get_data_addr(data->textures[3].img,
			&data->textures[3].bits_per_pixel,
			&data->textures[3].line_length, &data->textures[3].endian);
}
