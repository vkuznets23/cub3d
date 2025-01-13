# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "MLX42/MLX42.h"

# define S_W 1900               // screen width
# define S_H 1000               // screen height
# define TILE_SIZE 30           // tile size
# define FOV 60                 // field of view
# define ROTATION_SPEED 0.045   // rotation speed
# define PLAYER_SPEED 4         // player speed

# define COL_FL 0xB99470FF
# define COL_RF 0x89CFF3FF

//represenrts player position, angle, and movement flags
typedef struct  s_player
{
    int    plyr_x;     // player x position in pixels
    int    plyr_y;     // player y position in pixels
    double angle;      // player angle
    float  fov_rd;     // field of view in radians
    int    rot;        // rotation flag
    int    l_r;        // left right flag
    int    u_d;        // up down flag
}   t_player;

typedef struct s_ray //the ray structure
{
 double ray_ngl; // ray angle
 double distance; // distance to the wall
 int  flag;  // flag for the wall
} t_ray;

typedef struct s_data //the data structure
{
 char **map2d; // the map
 int  p_x;  // player x position in the map
 int  p_y;  // player y position in the map
 int  w_map;  // map width
 int  h_map;  // map height
} t_data;

typedef struct s_mlx //the mlx structure
{
 mlx_image_t  *img; // the image
 mlx_t   *mlx_p; // the mlx pointer
 t_ray   *ray; // the ray structure
 t_data   *dt; // the data structure
 t_player  *ply; // the player structure
} t_mlx;
