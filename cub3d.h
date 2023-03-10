#ifndef CUB3D_H
#define CUB3D_H

#define TILE 32
#define PI 3.14159265359
#define MVSPEED 1
#define TUSPEED 0.01
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"




typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;




typedef struct  s_mlx
{
    void *mlx;
    void *win;
    t_img *img;
    int window_hight;
    int window_width;
    double player_pos_x;
    double player_pos_y;
    char    **map;
    int     map_hight;
    int     map_width;
    double  player_angle;
    double  player_view_angle;
    int     player_field_of_view;
    int     player_move_direction;
    int     player_rotate_direction;
}               t_mlx;



#endif