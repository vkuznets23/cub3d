# ifndef CUB3D_H
# define DUB3D_

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 30       // ill need it for my textures (means that 1 tile is 30x30 px)
# define FOV 60             // field of view 60 is comon first person angle
# define ROTATION_SPEED 0.045   // rotation speed
# define PLAYER_SPEED 4         // player speed

typedef struct s_player
{
    int     player_x;
    int     player_y;       //player position in 2d
    double  angle;          //player viewing angle
    float   fov;            //players field of view
    int     rotation;
    int     left_right;
    int     up_down;
}   t_player;

typedef struct  s_ray
{
    double  ray_angle;
    double  distance;
    int     flag;           //flag for the wall
}   t_ray;


typedef struct  s_map
{
    char    **map;          //2d map grid
    int     pl_x;
    int     pl_y;
    int     w_map;
    int     h_map;
}   t_map;

typedef struct  s_mlx
{
    mlx_image_t *img;
    //mlx pointer is necessary to interact with the graphical window, handle events, 
    //and manage resources like textures, images, and graphics
    mlx_t       *mlx_p;
    t_ray       *ray;
    t_player    *player;
    t_map       *map;
}   t_mlx;

void    hook(t_mlx *mlx, int move_x, int move_y);
void    mlx_key(mlx_key_data_t keydata, void *ml);

float nor_angle(float angle);
int	unit_circle(float angle, char c);

void    cast_rays(t_mlx *mlx);

# endif
