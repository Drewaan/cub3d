/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:33 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 13:46:24 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ---------------- LIBRARIES ---------------- */
# include "../libft/include/libft.h"
# include "MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
/* ---------------- CONSTANTS ---------------- */
# define WIN_W 1280
# define WIN_H 720

/* ---------------- COLORS ---------------- */
typedef struct s_color
{
	int red;
	int green;
	int blue;
	int alpha;
}	t_color;


/* ---------------- TEXTURES ---------------- */
typedef struct s_tex
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	uint32_t		floor_color;
	uint32_t		ceil_color;
}	t_tex;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				tex_y;
	double			tex_step;
	double			tex_pos;
}	t_wall_tex;

/* ---------------- RAYCAST ---------------- */
typedef struct s_raycast
{
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		wall_x;
	double		wall_dist;
}	t_raycast;

/* ---------------- PLAYER ---------------- */
typedef struct s_player
{
	double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    double  speed;
    double  rot_speed;
    int     has_spawn;
}   t_player;
/* ---------------- MAP ---------------- */
typedef struct s_map
{
	char		**map_array;
	int			width;
	int			height;
}	t_map;

/* ---------------- GAME ---------------- */
typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_player	player;
	t_tex		tex;
	t_raycast	raycast;
	t_wall_tex	wall_tex;
}	t_game;

/* ---------------- INIT ---------------- */
void			init_game(t_game *game);
void			init_player(t_game *game);
void			init_map(t_map *map);

/* ---------------- PARSING ---------------- */
int				check_cub_extension(const char *file);
int				parse_cub(t_game *game, const char *file);
int				parse_config(t_game *g, char **lines, int *i);
int				parse_textures(t_game *game, char *line);
int				parse_colors(t_game *game, char *line);
int				parse_map(t_game *game, char **lines, int *i);
int				validate_map(t_map *map);
void			normalize_map(t_map *map);
int set_player_pos(t_game *g, char c, int y, int x);

// UTILS =========================================================

uint32_t	get_rgba(int r, int g, int b, int a);
int		valid_char(char c);

/* ---------------- TEXTURE UTILS ---------------- */
mlx_texture_t	*load_texture(char *path);
t_color			get_texture_pixel(mlx_texture_t *tex, int x, int y);
void			set_tex_params(t_wall_tex *wt, t_raycast *r);
void			get_wall_texture(t_game *game);
void    		get_wall_height(t_game *game, int x);
void			free_textures(t_game *g);
int				validate_all_textures(t_game *g);
void			cleanup_game(t_game *g);


/* ---------------- FREE ---------------- */
void			free_map(t_map *map);
void			ft_free_split(char **arr);

/* ---------------- CONTROLS ---------------- */
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);

/* ---------------- HOOKS ---------------- */
void			key_hook(mlx_key_data_t keydata, void *params);
void			rotate(t_player *p, double angle);
void			main_hook(void *params);

/* ---------------- DRAW / RAYCAST ---------------- */
void			draw_sky_and_floor(t_game *game, int x);
void			draw_stripe(t_game *game, int x, int start, int end);
int				dim_color(t_color *color, double dist);
void			raycast(t_game *game);

#endif
