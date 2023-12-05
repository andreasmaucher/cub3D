#include "cub3D.h"

void	ray_init(t_mdata *data)
{
	/* int i;
	int size; */

	data->ray.posx = (double)data->start_x + 0.5; //center in one grid cell
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
	data->ray.movespeed = 0.1;
	data->ray.rotspeed = 0.0873; //5 * (pi / 180)
	// i = 0;
	// size = 0;
/* 	while (i < 8)
	{
		size = TEX_WIDTH * TEX_HEIGHT;
		int* textureArray = (int*)malloc(size * sizeof(int));
		data->ray.texture_arr[i] = *textureArray;
	}
	dir_vector_init(data); */
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

// cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents
// right side is 1, center 0, left -1
// direction of the ray is calculated as sum of direction vector and part of the plane vector
void	dda_calculation(t_mdata *data)
{
	data->ray.hit = 0;
	data->ray.perpwalldist = 0;
	//printf("%f,%f,%f,%f\n", data->ray.dirx, data->ray.diry, data->ray.planx, data->ray.plany);
	data->ray.camerax = 2 * data->ray.x / (double)data->winx - 1; //divide by size of screen
	data->ray.raydirx = data->ray.dirx + data->ray.planx * \
						data->ray.camerax;
	data->ray.raydiry = data->ray.diry + data->ray.plany * \
						data->ray.camerax;
	// mapx and mapy represent the current square of the map the ray is in
	data->ray.mapx = (int)data->ray.posx;
	data->ray.mapy = (int)data->ray.posy;
	// distx and disty the distance the ray has to travel to go from 1 x-side to the next x-side 
	// or from 1 y-side to the next y-side
	// to avoid division by zero set it to a very high value
	if (data->ray.raydirx == 0)
		data->ray.deltadistx = 1e30;
	// fabs returns absolute value of floating points
	else
		data->ray.deltadistx = fabs(1 / data->ray.raydirx);
	if (data->ray.raydiry == 0)
		data->ray.deltadisty = 1e30;
	else
		data->ray.deltadisty = fabs(1 / data->ray.raydiry);
}

// prepares the necessary parameters for the drawing loop based on the direction
// of the rays and the distances to the next sides (walls)
void	step_sidedist(t_mdata *data)
{
	// this means the ray is pointing to the left
	if (data->ray.raydirx < 0)
	{
		data->ray.stepx = -1; //indicate stepping left
		// calculate distance to the next x-side
		data->ray.sidedistx = (data->ray.posx - data->ray.mapx) \
							* data->ray.deltadistx;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (data->ray.mapx + 1.0 - data->ray.posx) \
							* data->ray.deltadistx;
	}
	// this means the ray is pointing upward
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

// loop that increments the ray with 1 square every time until a wall is hit
//! for textures we need to know which side was hit
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
		data->ray.perpwalldist = fabs(data->ray.sidedistx - data->ray.deltadistx);
	else
		data->ray.perpwalldist = fabs(data->ray.sidedisty - data->ray.deltadisty);
	data->ray.lineheight = (int)(data->winy / data->ray.perpwalldist);
	data->ray.drawstart = -data->ray.lineheight / 2 + data->winy / 2;
	if (data->ray.drawstart < 0)
		data->ray.drawstart = 0;
	else
		data->ray.drawstart = data->ray.drawstart;
	data->ray.drawend = data->ray.lineheight / 2 + data->winy / 2;
	if (data->ray.drawend >= data->winy || data->ray.drawend < 0)
		data->ray.drawend = data->winy - 1;
	else
		data->ray.drawend = data->ray.drawend;
}

//! probably needs to change for textures!
int		drawing_function(t_mdata *data)
{
	int j;
	int i;

	j = -1;
	// calculate the height of the wall to be drawn
	data->ray.drawend = data->winy - data->ray.drawstart;
	i = data->ray.drawend;
	// fill the pixels above the wall with the ceiling color (data->c)
	//! what does this thing even do?!
	while (++j < data->ray.drawstart)
		data->main_data.addr[j * data->main_data.line_length / 4 +
			data->ray.x] = data->c;
	// Fill the pixels of the wall with a specific color (0x00ff6000 in this case)
	//! replace this constant color with with logic for textures
	//! based on the rays intersection point with the wall
	while (++j <= data->ray.drawend)
	{
		data->main_data.addr[j * data->main_data.line_length / 4 +
			data->ray.x] = 0x00ff6000;
	}
	j = i;
	// Fill the pixels below the wall with the floor color (data->f)
	while (++j < data->winy)
		data->main_data.addr[j * data->main_data.line_length / 4 +
			data->ray.x] = data->f;
	return (0);
}

int		raycasting(t_mdata *data)
{
	data->ray.x = 0;
	// loop that goes through every x, so there isn't 
	//a calculation for every pixel of the screen, but only
	// for every vertical stripe
	while (data->ray.x < data->winx)
	{
		dda_calculation(data);
		step_sidedist(data);
		drawing_function(data);
		data->ray.x++;
	}
	mlx_put_image_to_window(data->main_data.mlx_ptr, data->main_data.mlx_win,
			data->main_data.img, 0, 0);
	move_forward_back(data);
	move_left_right(data);
	rotate_right_left(data);
	return (0);
}

int		mlx_main(t_mdata *data)
{
	if (!(data->main_data.mlx_ptr = mlx_init()))
		error_handle(data, "Mlx not initialized\n");
	data->main_data.img = mlx_new_image(data->main_data.mlx_ptr, data->winx, data->winy);
	data->main_data.addr = (int *)mlx_get_data_addr(data->main_data.img, &data->main_data. \
	bits_per_pixel, &data->main_data.line_length, &data->main_data.endian);
	data->main_data.mlx_win = mlx_new_window(data->main_data.mlx_ptr, data->winx,
			data->winy, "CUB3D");
	mlx_hook(data->main_data.mlx_win, 33, 1L << 17, clean_exit, data);
	mlx_hook(data->main_data.mlx_win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->main_data.mlx_ptr, raycasting, data);
	mlx_hook(data->main_data.mlx_win, 3, 1L << 1, key_release, data);
	mlx_loop(data->main_data.mlx_ptr);
	return (0);
}
