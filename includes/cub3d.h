/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:33 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/11/24 19:44:12 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

# define WIN_W 800
# define WIN_H 600
# define TILE 10

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				alpha;
}					t_color;

typedef struct s_data
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	t_color			floor;
	t_color			ceiling;
	int				map_start;
	int				map_lines;
}					t_data;

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
}					t_player;

typedef struct s_map
{
	char			**map_array;
	int				map_w;
	int				map_h;
}					t_map;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	int				text_x;
	int				text_y;
	double			tex_pos;
	double			tex_step;
}					t_wall_tex;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				floor_color;
	int				ceiling_color;
}					t_texture;

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
}					t_ray;

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

int					check_args(int argc, char **argv);

// RAYCAST =========================================================

void				ray_refresh(t_ray *ray, t_player *player, int x);
void				ray_dir(t_ray *ray, t_player *player);
void				check_hit(t_game *game);
void				set_dist(t_game *game);
void				raycast(t_game *game);

// DRAW =========================================================

void				draw_sky_and_floor(t_game *game, int x);

// UTILS =========================================================

int					get_rgba(int r, int g, int b, int a);

// HOOKS ===========================================================

void				key_hook(mlx_key_data_t keydata, void *params);
void				main_hook(void *params);

// CONTROLS =============================================================

void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_right(t_game *game);
void				move_left(t_game *game);
void				rotate(t_player *player, float angle);

// FREE_UTILS =========================================================

void				game_over(t_game *game);
void				free_data(t_data *data);

// DRAW =========================================================

void				draw_sky_and_floor(t_game *game, int x);
int					dim_color(t_color *color, double dist);
void				draw_stripe(t_game *game, int x, int start, int end);
void				get_wall_height(t_game *game, int x);

// DRAW =========================================================

t_color				get_texture_pixel(mlx_texture_t *texture, int x, int y);

// PARSING ======================================================
void				parse_file(t_data *d, char *path);
void				check_file_extension(char *path);
void				check_identifiers(t_data *d);
void				load_map(t_data *d, char **lines);
void				check_map(t_data *d);
void				load_textures(t_data *d);
void				init_player(t_data *d);
char				**read_file_to_array(char *path);
char				**dup_map(t_data *d);
void				free_map(char **m);
void				error_exit(char *msg);
void				parse_color(t_color *c, char *str);

#endif