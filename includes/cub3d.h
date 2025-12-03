/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:33 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/02 18:20:22 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../libft/include/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

# define WIN_W 1366
# define WIN_H 768
# define TILE 10

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				alpha;
}	t_color;

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
}	t_data;

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
	int				map_w;
	int				map_h;
}	t_map;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	double			tex_step;
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

// ----- PATHS -----
typedef struct s_paths
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}			t_paths;

// ---- PARSER STRUCT ----
typedef struct s_parser
{
	t_paths	paths;
	t_color	floor_color;
	t_color	ceil_color;

	char	**map;
	int		map_w;
	int		map_h;

	int		player_x;
	int		player_y;
	char	player_dir;

	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

}			t_parser;


// CHECK_UTILS =========================================================

int		check_args(int argc, char **argv);
void	check_map_parser(t_parser *p);

// CONTROLS =============================================================

void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);
void	rotate(t_player *player, float angle);

// DATA_TO_GAME =========================================================

void	data_to_game(t_parser *p, t_game *g);

// DRAW =========================================================

void	draw_sky_and_floor(t_game *game, int x);
int		dim_color(t_color *color, double dist);
void	draw_stripe(t_game *game, int x, int start, int end);
void	get_wall_height(t_game *game, int x);

// DUP_MAP =========================================================

char	**dup_map(t_parser *p);

// FREE_UTILS =========================================================

void	free_parser(t_parser *p);
void	error_exit(char *msg);
void	free_split(char **arr);
void	game_over(t_game *g);

// HOOKS ===========================================================

void	key_hook(mlx_key_data_t keydata, void *params);
void	main_hook(void *params);

// INITIALIZE =======================================================

void	set_plane(t_player *player, char dir);
void	set_dir(t_player *player, char dir);
void	parser_init(t_parser *p);

// LOAD_MAP_PARSER =======================================================

void	load_map_parser(t_parser *p, char **m);

// PARSE_COLOR =======================================================

void	parse_color(t_color *c, char *s);

// PARSE_FILE =========================================================

void	parse_file(t_parser *p, char *path);

// RAYCAST =========================================================

void	ray_refresh(t_ray *ray, t_player *player, int x);
void	ray_dir(t_ray *ray, t_player *player);
void	check_hit(t_game *game);
void	set_dist(t_game *game);
void	raycast(t_game *game);

// READ_FILE_TO_ARRAY =========================================================

char	**read_file_to_array(char *path);

// TEXTURE =========================================================

t_color	get_texture_pixel(mlx_texture_t *texture, int x, int y);
void	get_wall_texture(t_game *game);
void	set_tex_params(t_wall_tex *wall_tex, t_ray *ray);

// UTILS =========================================================

int		get_rgba(int r, int g, int b, int a);
int		valid_char(char c);

#endif
