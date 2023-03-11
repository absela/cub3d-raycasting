
#include "cub3d.h"





void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double to_radian(double t)
{
	return (t * (PI / 180));
}

void dda(t_mlx *data, double X0, double Y0, double X1, double Y1, double angle, double scale,int color)
{
    X1 = X1 + cos(angle) *scale;
    Y1 = Y1 + sin(angle) * scale;
    // printf("The X1 is : %f\n",X1/40);
    // printf("The Y1 is : %f\n",Y1/40);
    double dx = X1 - X0;
    double dy = Y1 - Y0;

    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    //printf("steps is : %f\n",steps);
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;
    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(data->img,X0,Y0,color);
        X0 += Xinc;
        Y0 += Yinc;
    }
}

void cast_All_rays(t_mlx *mlx)
{
	double ray_angle = mlx->player_view_angle - to_radian(mlx->player_field_of_view/2);
    ray_angle = mlx->player_view_angle - to_radian(mlx->player_field_of_view/2);
    int i = 0;
   while(i < 60 )
   {
            dda(mlx,mlx->player_pos_x,mlx->player_pos_y,mlx->player_pos_x,mlx->player_pos_y,ray_angle,90,0xFFFFFF);
            ray_angle += to_radian(mlx->player_field_of_view)/60 ;
            i++;
  }
}

double	limit_angles(double ra)
{
	if (ra > 360)
		ra = ra - 360;
	if (ra < 0)
		ra = 360 + ra;
	return (ra);
}



void    draw_square(int i, int j, t_mlx *mlx)
{
	int x = j * TILE;
	int y;

	while(x < j * TILE + (TILE - 1))
	{
		y = i * TILE;
		while(y < i * TILE + (TILE - 1))
		{
			my_mlx_pixel_put(mlx->img,x,y, 0x99e6ff);
			y++;
		}
		x++;
	}
}

void    draw_squaref(int i, int j, t_mlx *mlx)
{
	int x = j * TILE;
	int y;

	while(x < j * TILE + (TILE - 1))
	{
		y = i * TILE;
		while(y < i * TILE + (TILE - 1))
		{
			my_mlx_pixel_put(mlx->img,x,y, 0x8D5B4C);
			y++;
		}
		x++;
	}
}


void    draw_world_2d(t_mlx *mlx)
{
	int i = 0;
	int j;
	while(mlx->map[i])
	{
		j = 0;
		while(mlx->map[i][j])
		{
			if(mlx->map[i][j] == '1')
				draw_square(i,j,mlx);
			if(mlx->map[i][j] == '0')
				draw_squaref(i,j,mlx);
			j++;
		}
		i++;
	}
}


void    player_position_init(t_mlx  *mlx)
{
	int i;
	int j;

	i = 0;

	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' || mlx->map[i][j] == 'E' || mlx->map[i][j] == 'W')
			{
				mlx->player_pos_x = (double)((j * TILE));
				mlx->player_pos_y = (double)((i * TILE));
				return ;
			}
			j++;
		}
		i++;
	}
}


int get_map_hight(char  **map)
{
	int i = 0;

	while(map[i])
	{
		i++;
	}
	return (i);
}

char	**r_map(char	*str)
{
	int		check;
	int		fd;
	char	*buf;
	char	*map;
	char    **res;

	map = ft_strdup("");
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("unable to open the map!!\n");
		exit(1);
	}
	buf = malloc(2);
	check = read(fd, buf, 1);
	buf[1] = '\0';
	while (check > 0)
	{
		map = ft_strjoin(map, buf);
		check = read(fd, buf, 1);
		buf[1] = '\0';
	}
	free(buf);
	res = ft_split(map, '\n');
	return (res);
}


void	initialize_player(t_mlx	*mlx)
{
	player_position_init(mlx);
	mlx->player_field_of_view = 90;
	mlx->player_view_angle = 60;
}


int	on_keydown(int keycode, t_mlx *mlx)
{
	if (keycode == 13)
		mlx->player_move_direction = 1;
	if (keycode == 123)
		mlx->player_rotate_direction = -1;
	if (keycode == 1)
		mlx->player_move_direction = -1;
	if (keycode == 124)
		mlx->player_rotate_direction = 1;
	if (keycode == 53)
		exit(0);
	return 0;
		
}

int	on_keyup(int keycode, t_mlx *mlx)
{
	if (keycode == 13 || keycode == 1)
		mlx->player_move_direction = 0;
	if (keycode == 123 || keycode == 124)
		mlx->player_rotate_direction = 0;
	return 0;
}

void	move_player(t_mlx	*mlx)
{
	double xjdida;
	double yjdida;

	xjdida = cos(mlx->player_view_angle) * mlx->player_move_direction * MVSPEED;
	yjdida = sin(mlx->player_view_angle)  * mlx->player_move_direction * MVSPEED;
	if (mlx->map[(int)(mlx->player_pos_y + yjdida) / TILE][(int)(mlx->player_pos_x + xjdida) / TILE] != '1')
	{
		mlx->player_pos_x += xjdida;
		mlx->player_pos_y += yjdida;
	}
}

void	rotate_player(t_mlx	*mlx)
{
	mlx->player_view_angle += mlx->player_rotate_direction * TUSPEED;
	mlx->player_view_angle = limit_angles(mlx->player_view_angle); 
}


int	every_frame(t_mlx	*mlx)
{
	move_player(mlx);
	rotate_player(mlx);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = mlx_new_image(mlx->mlx,mlx->map_width * TILE, mlx->map_hight * TILE);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	draw_world_2d(mlx);
	cast_All_rays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_mlx *data;
	(void)ac;
	{
	data = (t_mlx *)malloc(sizeof(t_mlx));
	data->map = r_map(av[1]);
	data->img = (t_img *)malloc(sizeof(t_img));
	data->mlx = mlx_init();
	data->map_width = ft_strlen(data->map[0]);
	data->map_hight = get_map_hight(data->map);
	data->window_hight = data->map_hight * TILE;
	data->window_width = data->map_width * TILE;
	data->win = mlx_new_window(data->mlx, data->window_width, data->window_hight, "Cub3D");
	initialize_player(data);
	data->img->img = mlx_new_image(data->mlx,data->map_width * TILE, data->map_hight * TILE);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	}
	mlx_loop_hook(data->mlx, every_frame, data);
	mlx_hook(data->win, 2, 0, on_keydown, data);
	mlx_hook(data->win, 3, 0, on_keyup, data);
	mlx_loop(data->mlx);
}