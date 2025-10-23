/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:33 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/10/23 14:12:06 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../libft/include/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

# define WIN_W 800
# define WIN_H 600
# define TILE 10

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				alpha;
}	t_color;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			speed;
	double			rotate_speed;
}	t_player;

typedef struct s_map
{
	char			**map_array;
	int				win_w;
	int				win_h;
}	t_map;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	int				text_x;
	int				text_y;
	double			text_pos;
	double			text_step;
}	t_wall_tex;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				floor_color;
	int				ceiling_color;
}	t_texture;

typedef struct s_ray
{
	double			camera;
	double			ray_x;
	double			ray_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wall_dist;
	double			wall_x;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side_hit;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			map;
	t_player		player;
	t_texture		textures;
	t_wall_tex		wall_tex;
	t_ray			raycast;
}					t_game;

// CHECK_UTILS =========================================================

int	check_args(int argc, char**argv);

// RAYCAST =========================================================

void	ray_refresh(t_ray *ray, t_player *player, int x);
void	ray_dir(t_ray *ray, t_player *player);
void	check_hit(t_game *game);
void	set_dist(t_game *game);
void	raycast(t_game *game);

// DRAW =========================================================

void	draw_sky_and_floor(t_game *game, int x);

// UTILS =========================================================

int	get_rgba(int r, int g, int b, int a);

#endif