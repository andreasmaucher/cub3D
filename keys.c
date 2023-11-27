#include "cub3D.h"

int		key_press(int keycode, t_mdata *data)
{
	//printf("%d\n", keycode);
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
	else if (keycode == 111)
	{
		data->winx = data->winx + 10;
		data->winy = data->winy + 10;
		change_win(data);
		return (mlx_main(data));
		
	}
	else if (keycode == 65307)
		clean_exit(data);
	return (1);
}

int		key_release(int keycode, t_mdata *data)
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

void	move_forward_back(t_mdata *data)
{
	if (data->main_data.forward == 1)
	{
		if (data->map[(int)(data->ray.posx + (data->ray.dirx * data->
						ray.movespeed * 2))][(int)data->ray.posy] == 0)
			data->ray.posx += data->ray.dirx * data->ray.movespeed;
		if (data->map[(int)(data->ray.posx)][(int)(data->ray.posy +
					(data->ray.diry * data->ray.movespeed * 2))] == 0)
			data->ray.posy += data->ray.diry * data->ray.movespeed;
	}
	if (data->main_data.back == 1)
	{
		if (data->map[(int)(data->ray.posx - (data->ray.dirx * data->
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
		if (data->map[(int)(data->ray.posx + data->ray.diry *
					(data->ray.movespeed * 2))][(int)data->ray.posy] == 0)
			data->ray.posx += data->ray.diry * data->ray.movespeed;
		if (data->map[(int)data->ray.posx][(int)(data->ray.posy -
					data->ray.dirx *
					(data->ray.movespeed * 2))] == 0)
			data->ray.posy -= data->ray.dirx * data->ray.movespeed;
	}
	if (data->main_data.left == 1)
	{
		if (data->map[(int)(data->ray.posx - data->ray.diry *
					(data->ray.movespeed * 2))][(int)data->ray.posy] == 0)
			data->ray.posx -= data->ray.diry * data->ray.movespeed;
		if (data->map[(int)data->ray.posx][(int)(data->ray.posy +
					data->ray.dirx *
					(data->ray.movespeed * 2))] == 0)
			data->ray.posy += data->ray.dirx * data->ray.movespeed;
	}
}

void	rotate_right_left(t_mdata *data)
{
	double oldplanx = 0;
	double olddirx = 0;

	oldplanx = data->ray.planx;
	olddirx = data->ray.dirx;
	if (data->main_data.rotate_right == 1)
	{
		data->ray.dirx = data->ray.dirx * cos(-data->ray.rotspeed) -
			data->ray.diry * sin(-data->ray.rotspeed);
		data->ray.diry = olddirx * sin(-data->ray.rotspeed) +
			data->ray.diry * cos(-data->ray.rotspeed);
		data->ray.planx = data->ray.planx * cos(-data->ray.rotspeed)
			- data->ray.plany * sin(-data->ray.rotspeed);
		data->ray.plany = oldplanx * sin(-data->ray.rotspeed) +
			data->ray.plany * cos(-data->ray.rotspeed);
	}
	rotate_left(data, olddirx);
}

void	rotate_left(t_mdata *data, double olddirx)
{
	double oldplanx = 0;

	if (data->main_data.rotate_left == 1)
	{
		olddirx = data->ray.dirx;
		oldplanx = data->ray.planx;
		data->ray.dirx = data->ray.dirx * cos(data->ray.rotspeed) -
			data->ray.diry * sin(data->ray.rotspeed);
		data->ray.diry = olddirx * sin(data->ray.rotspeed) + data->
			ray.diry * cos(data->ray.rotspeed);
		data->ray.planx = data->ray.planx * cos(data->ray.rotspeed) -
			data->ray.plany * sin(data->ray.rotspeed);
		data->ray.plany = oldplanx * sin(data->ray.rotspeed) +
			data->ray.plany * cos(data->ray.rotspeed);
	}
}

int		clean_exit(t_mdata *data)
{
	if (data->main_data.img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->main_data.img);
	if (data->main_data.mlx_win)
		mlx_destroy_window(data->main_data.mlx_ptr, data->main_data.mlx_win);
	mlx_destroy_display(data->main_data.mlx_ptr);
	free(data->main_data.mlx_ptr);
	exit(0);
	return (0);
}

int		change_win(t_mdata *data)
{
	if (data->main_data.img)
		mlx_destroy_image(data->main_data.mlx_ptr, data->main_data.img);
	if (data->main_data.mlx_win)
		mlx_destroy_window(data->main_data.mlx_ptr, data->main_data.mlx_win);
	mlx_destroy_display(data->main_data.mlx_ptr);
	free(data->main_data.mlx_ptr);
	return (0);
}
/* int handle_resize(int button, int x, int y, t_mdata *data)
{
    int	dx;
	int	dy;
	int new_width;
	int new_height;

	if (button == 1)
	{
        data->resize_x = x;
        data->resize_y = y;
        data->is_resized = 1;
    }
    else if (button == 3)
        data->is_resized = 0;
    if (data->is_resized) 
	{
		dx = x - data->resize_x;
        dy = y - data->resize_y;
        new_width = data->initial_width + dx;
        new_height = data->initial_height + dy;
        mlx_clear_window(data->main_data.mlx_ptr, data->main_data.mlx_win);
        data->initial_width = new_width;
        data->initial_height = new_height;
		data->winx = new_width;
		data->winy = new_height;
    }
	return (0);
} */