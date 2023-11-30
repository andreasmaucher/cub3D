#ifndef CUB3D_H
#define CUB3D_H

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define BUFFER_SIZE	4096
# define MAX_PATH	4096
# define MAX_SIZE	700
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

typedef struct		s_idata
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				minimapechelle;
	int				width;
	int				height;
}					t_idata;

typedef struct		s_ray
{
	double			posx; //position vector of the player
	double			posy;
	double			dirx; //direction of the player
	double			diry;
	double			planx; //camera plane of the player
	double			plany;
	double			raydirx; //dirX + planeX * cameraX
	double			raydiry;
	double			camerax; //x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1
	int				mapx; //current square of the map the ray is in
	int				mapy;
	double			sidedistx; //initially the distance the ray has to travel from its start position to the first x-side and the first y-side
	double			sidedisty;
	double			deltadistx; //the distance the ray has to travel to go from 1 x-side to the next x-sid : abs(1 / rayDirX)
	double			deltadisty;
	double			perpwalldist; //perpenducular distance not Euclidean: the length of the ray. if (side == 0) -> sideDistX - deltaDistX || if (side == 1) -> sideDistY - deltaDistY
	int				stepx; //the direction of the ray: either -1 or +1 (negative or positive x-direction)
	int				stepy;
	int				hit; //whether or not the coming loop may be ended, and side will contain if an x-side or a y-side of a wall was hit.  if (Map[mapX][mapY] > 0)->hit = 1;
	int				side; //which side of the wall is hit & what wall was hit with mapX and mapY
	int				lineheight; //the height of the line that has to be drawn on screen, the inverse of perpWallDist multiplied by **h(the height in pixels of the screen)** -> h / perpWallDist: this can be scaled by any default number
	int				drawstart; //start and end position of where we should really draw. he center of the wall should be at the center of the screen, and if these points lie outside the screen, they're capped to 0 or h-1. -> -lineHeight / 2 + h / 2
	int				drawend; //lineHeight / 2 + h / 2
	double			movespeed; //The speed modifiers use frameTime, and a constant value, to determinate the speed of the moving and rotating of the input keys
	double			rotspeed;
	int				x;
	int				texture;
	u_int32_t		buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	int				texture_arr[8];
}					t_ray;

typedef struct		s_mdata
{
	int		i;
	int		error;
	int		rows;
	int		columns;
	int		f;
	int		c;
	int		wrongcharmap;
	int		x;
	int		winx;
	int		winy;
	char	start;
	int		start_x;
	int		start_y;
	int		map[MAX_SIZE][MAX_SIZE];
	char	no[MAX_PATH];
	char	so[MAX_PATH];
	char	ea[MAX_PATH];
	char	we[MAX_PATH];
	char	*err_msg;
	t_idata textures[4];
	t_idata	main_data;
	t_ray	ray;
}	t_mdata;

void	parser(char *file_name, t_mdata *data);
int		color_finder(char *str, t_mdata *data);
void	floor_ceiling(char *str, t_mdata *data);
int		ft_strlen(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_subbuff(char *buff, int start, int len);
int		get_next_line(int fd, char **line, t_mdata *data);
char	*ft_strjoin(char *s1, char *s2);
int		ft_free_buff(char **buff, t_mdata *data);
int		ft_eof(int ret, char **buff, char **line);
int		ft_copy(char **line, char **buff);
int		ft_check(char *str);
int		pre_check(char *str, t_mdata *data);
int		main(int argc, char **argv);
void	error_handle(t_mdata *data, char *str);
void	initialize(t_mdata *data);
int		color_check(char *str);
int		open_check(char *file_name, t_mdata *data);
void	textures(char *s, t_mdata *data);
int		texture_extractor(char *str, char *texture, t_mdata *data);
int		is_map(char *str, t_mdata *data);
void	map_check(char *str, t_mdata *data);
int		space_sub(t_mdata *data, char c, int i, int size);
int		start_point(char c, t_mdata *data, int i, int j);
int		copy_map(char *str, t_mdata *data);
int		create_map(char *file_name, t_mdata *data);
void	print_map(t_mdata *data);
int		wall_check(t_mdata *data, char *str, int row);

void	ray_init(t_mdata *data);
void	dir_vector_init(t_mdata *data);
int		raycasting(t_mdata *data);
int		mlx_main(t_mdata *data);
void	dda_calculation(t_mdata *data);
void	step_sidedist(t_mdata *data);
void	drawing_loop(t_mdata *data);
void	drawing_cal(t_mdata *data);
int		drawing_function(t_mdata *data);

int		clean_exit(t_mdata *data);
void	image_swap(t_mdata *data);
void	rotate_left(t_mdata *data, double olddirx);
void	rotate_right_left(t_mdata *data);
void	move_left_right(t_mdata *data);
void	move_forward_back(t_mdata *data);
int		key_release(int keycode, t_mdata *data);
int		key_press(int keycode, t_mdata *data);
int		handle_resize(int button, int x, int y, t_mdata *data);
int		change_win(t_mdata *data);

#endif