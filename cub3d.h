#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 64
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

typedef struct s_player
{
	int		player_x;
	int		player_y;
	double	angle;
	float	fov;
	int		rotation;
	int		left_right;
	int		up_down;
}	t_player;

//flag for the wall
typedef struct s_ray
{
	int		index;
	int		flag;
	double	ray_angle;
	double	distance;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
}	t_ray;

typedef struct s_data
{
	char	**map;
	int		pl_x;
	int		pl_y;
	int		w_map;
	int		h_map;
	int		ff_c[3];
	int		cc_c[3];
}	t_data;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
}	t_textures;

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*mlx_p;
	t_ray		*ray;
	t_player	*player;
	t_textures	*textures;
	t_data		*dt;
}	t_mlx;

//moving
void	hook(t_mlx *mlx, int move_x, int move_y);
void	mlx_key(mlx_key_data_t keydata, void *ml);

//raycasting
void	cast_rays(t_mlx *mlx);

//raycasting_utils
float	nor_angle(float angle);
int		unit_circle(float angle, char c);
int		inter_check(float angle, float *inter, float *step, int is_horizon);
int		wall_hit(float x, float y, t_mlx *mlx);

//rendering
void	render_cub(t_mlx *mlx, int ray);

//utils
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		get_rgb(int R, int G, int B, int a);
int		reverse_bytes(int c);
void	find_n_position(t_data *dt);
int		count_lines(char **map);

//exit
void	ft_exit(t_mlx *mlx);
#endif
