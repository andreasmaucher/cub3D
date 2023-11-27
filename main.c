#include "cub3D.h"

void	initialize(t_mdata *data)
{
	data->c = -1;
	data->f = -1;
	data->error = 0;
	data->columns = 0;
	data->rows = 0;
	data->wrongcharmap = 0;
	data->x = 0;
	data->start = '\0';
	data->winx = 680;
	data->winy = 460;
	data->err_msg = NULL;
	//memset(data->map, 0, sizeof(data->map));
	memset(data->ea, 0, MAX_PATH);
	memset(data->we, 0, MAX_PATH);
	memset(data->no, 0, MAX_PATH);
	memset(data->so, 0, MAX_PATH);
}

int		pre_check(char *str, t_mdata *data)
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
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		parser(str, data);
	else
		error_handle(data, "invalid map\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_mdata	data;

	initialize(&data);
	if (argc == 2)
		pre_check(argv[1], &data);
	else
		printf("Error\ninvalid arguments\n");
}