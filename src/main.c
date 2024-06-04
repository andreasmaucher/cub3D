/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:32:08 by ashojach          #+#    #+#             */
/*   Updated: 2024/06/05 01:10:31 by amaucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	initialize(t_mdata *data)
{
	data->c = -1;
	data->f = -1;
	data->columns = 0;
	data->rows = 0;
	data->x = 0;
	data->start = '\0';
	data->wx = 680;
	data->wy = 460;
	data->err_msg = NULL;
	data->bytes = 1;
	data->mini = -1;
	data->inmap = 0;
	data->newline = 0;
	data->clean_exit = 0;
	data->main_data.last_x = -1;
	data->main_data.last_y = -1;
	init_image(data);
	memset(data->map, 0, sizeof(data->map));
	memset(data->ea, 0, MAX_PATH);
	memset(data->we, 0, MAX_PATH);
	memset(data->no, 0, MAX_PATH);
	memset(data->so, 0, MAX_PATH);
}

void	print_map(t_mdata *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("%d:", i + 1);
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			printf("%d ", data->map[i][j]);
			j++;
		}
		i++;
		printf("\n%d:", i + 1);
	}
}

int	pre_check(char *str, t_mdata *data)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			error_handle(data, "invalid map\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b'
		&& str[i + 4] == '\0')
		parser(str, data);
	else
		error_handle(data, "invalid map\n");
	return (0);
}

int	mlx_main(t_mdata *data)
{
	ray_init(data);
	data->main_data.mlx_ptr = mlx_init();
	if (!(data->main_data.mlx_ptr))
		error_handle(data, "Mlx not initialized\n");
	load_texture(data);
	minimap_init(data);
	data->main_data.mlx_win = mlx_new_window(data->main_data.mlx_ptr,
			data->wx, data->wy, "CUB3D");
	data->main_data.img = mlx_new_image(data->main_data.mlx_ptr, data->wx,
			data->wy);
	data->main_data.addr = (int *)mlx_get_data_addr(data->main_data.img,
			&data->main_data. \
	bits_per_pixel, &data->main_data.line_length, &data->main_data.endian);
	mlx_hook(data->main_data.mlx_win, 33, 1L << 17, clean_exit, data);
	mlx_hook(data->main_data.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->main_data.mlx_win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->main_data.mlx_ptr, raycasting, data);
	mlx_hook(data->main_data.mlx_win, 3, 1L << 1, key_release, data);
	mlx_loop(data->main_data.mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mdata	data;

	initialize(&data);
	if (argc == 2)
		pre_check(argv[1], &data);
	else
		printf("Error\ninvalid arguments\n");
}
