#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

static inline uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
}

t_color get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	t_color color;
	uint8_t *pixel;

	color.red = color.green = color.blue = color.alpha = 0;
	if (!texture) return color;

	if (x < 0)
		x = 0;
	if (x >= (int)texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)texture->height)
		y = texture->height - 1;

	pixel = texture->pixels + (y * texture->width + x) * texture->bytes_per_pixel;
	color.red = pixel[0];
	color.green = pixel[1];
	color.blue = pixel[2];
	if (texture->bytes_per_pixel >= 4)
		color.alpha = pixel[3];
	else
		color.alpha = 255;
	return color;
}

void get_wall_texture(t_game *game)
{
	if (!game) return;
	game->wall_tex.tex = NULL;
	if (game->raycast.side_hit == 0)
	{
		if (game->raycast.ray_x > 0)
			game->wall_tex.tex = game->textures.west;
		else
			game->wall_tex.tex = game->textures.east;
	}
	else
	{
		if (game->raycast.ray_y > 0)
			game->wall_tex.tex = game->textures.north;
		else
			game->wall_tex.tex = game->textures.south;
	}
}
void set_tex_params(t_wall_tex *wall_tex, t_ray *ray)
{
	if (!wall_tex || !ray || !wall_tex->tex)
		return;

	ray->wall_x -= floor(ray->wall_x);

	if (ray->side_hit == 0)
	{
		if (ray->step_x > 0)
			wall_tex->tex_x = (int)(ray->wall_x * (double)(wall_tex->tex->width));
		else
			wall_tex->tex_x = wall_tex->tex->width - (int)(ray->wall_x * (double)(wall_tex->tex->width)) - 1;
	}
	else
	{
		if (ray->step_y > 0)
			wall_tex->tex_x = wall_tex->tex->width - (int)(ray->wall_x * (double)(wall_tex->tex->width)) - 1;
		else
			wall_tex->tex_x = (int)(ray->wall_x * (double)(wall_tex->tex->width));
	}
	if (wall_tex->tex_x < 0)
		wall_tex->tex_x = 0;
	if (wall_tex->tex_x >= (int)wall_tex->tex->width)
		wall_tex->tex_x = wall_tex->tex->width - 1;
}

void ray_refresh(t_ray *ray, t_player *player, int x)
{
	ray->hit = 0;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->camera = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera;

	ray->delta_dist_x = (ray->ray_x == 0.0) ? 1e30 : fabs(1.0 / ray->ray_x);
	ray->delta_dist_y = (ray->ray_y == 0.0) ? 1e30 : fabs(1.0 / ray->ray_y);
}

void ray_dir(t_ray *ray, t_player *player)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void check_hit(t_game *game)
{
	int max_y = game->map.map_h;
	int max_x = game->map.map_w;

	while (game->raycast.hit == 0)
	{
		if (game->raycast.side_dist_x < game->raycast.side_dist_y)
		{
			game->raycast.side_dist_x += game->raycast.delta_dist_x;
			game->raycast.map_x += game->raycast.step_x;
			game->raycast.side_hit = 0;
		}
		else
		{
			game->raycast.side_dist_y += game->raycast.delta_dist_y;
			game->raycast.map_y += game->raycast.step_y;
			game->raycast.side_hit = 1;
		}
		if (game->raycast.map_x < 0 || game->raycast.map_x >= max_x
			|| game->raycast.map_y < 0 || game->raycast.map_y >= max_y)
		{
			game->raycast.hit = 1;
			break;
		}
		if (game->map.map_array[game->raycast.map_y][game->raycast.map_x] == '1')
			game->raycast.hit = 1;
	}
}

void set_dist(t_game *game)
{
	if (game->raycast.side_hit == 0)
		game->raycast.wall_dist = game->raycast.side_dist_x - game->raycast.delta_dist_x;
	else
		game->raycast.wall_dist = game->raycast.side_dist_y - game->raycast.delta_dist_y;

	if (game->raycast.wall_dist <= 0.000001)
		game->raycast.wall_dist = 0.000001;

	if (game->raycast.side_hit == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.wall_dist * game->raycast.ray_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.wall_dist * game->raycast.ray_x;
}

void draw_vertical_line(mlx_image_t *img, int x, int start, int end, uint32_t color)
{
	if (!img) return;
	if (x < 0 || x >= WIN_W) return;
	if (start < 0) start = 0;
	if (end >= WIN_H) end = WIN_H - 1;
	for (int y = start; y <= end; ++y)
		mlx_put_pixel(img, x, y, color);
}

void raycast_frame(t_game *game)
{
	int x;

	if (!game || !game->img)
		return;

	for (int y = 0; y < WIN_H / 2; ++y)
		for (int xx = 0; xx < WIN_W; ++xx)
			mlx_put_pixel(game->img, xx, y, rgba(120,180,255,255));
	for (int y = WIN_H / 2; y < WIN_H; ++y)
		for (int xx = 0; xx < WIN_W; ++xx)
			mlx_put_pixel(game->img, xx, y, rgba(80,80,80,255));

	for (x = 0; x < WIN_W; ++x)
	{
		ray_refresh(&game->raycast, &game->player, x);
		ray_dir(&game->raycast, &game->player);
		check_hit(game);
		set_dist(game);

		int line_height = (int)(WIN_H / game->raycast.wall_dist);
		int draw_start = -line_height / 2 + WIN_H / 2;
		int draw_end = line_height / 2 + WIN_H / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= WIN_H) draw_end = WIN_H - 1;

		get_wall_texture(game);
		if (game->wall_tex.tex)
		{
			set_tex_params(&game->wall_tex, &game->raycast);
			game->wall_tex.tex_step = (double)game->wall_tex.tex->height / (double)line_height;
			game->wall_tex.tex_pos = (draw_start - WIN_H / 2 + line_height / 2) * game->wall_tex.tex_step;
		}

		uint32_t fallback = rgba(200,40,40,255);

		for (int y = draw_start; y <= draw_end; ++y)
		{
			uint32_t color = fallback;
			if (game->wall_tex.tex)
			{
				int tex_y = (int)game->wall_tex.tex_pos;
				/* clamp */
				if (tex_y < 0) tex_y = 0;
				if (tex_y >= (int)game->wall_tex.tex->height) tex_y = game->wall_tex.tex->height - 1;

				t_color px = get_texture_pixel(game->wall_tex.tex, game->wall_tex.tex_x, tex_y);
				color = rgba((uint8_t)px.red, (uint8_t)px.green, (uint8_t)px.blue, (uint8_t)px.alpha);

				game->wall_tex.tex_pos += game->wall_tex.tex_step;
			}
			if (game->raycast.side_hit == 1)
			{
				uint8_t r = (color >> 24) & 0xFF;
				uint8_t g = (color >> 16) & 0xFF;
				uint8_t b = (color >> 8) & 0xFF;
				uint8_t a = color & 0xFF;
				color = rgba(r/2, g/2, b/2, a);
			}
			mlx_put_pixel(game->img, x, y, color);
		}
	}
}

void move_forward(t_game *game)
{
	double newposx = game->player.pos_x + game->player.dir_x * game->player.speed;
	double newposy = game->player.pos_y + game->player.dir_y * game->player.speed;
	double margin = 0.2;

	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx + game->player.dir_x * margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy + game->player.dir_y * margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void move_backward(t_game *game)
{
	double newposx = game->player.pos_x - game->player.dir_x * game->player.speed;
	double newposy = game->player.pos_y - game->player.dir_y * game->player.speed;
	double margin = 0.2;

	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx - game->player.dir_x * margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy - game->player.dir_y * margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void move_right(t_game *game)
{
	double newposx = game->player.pos_x + game->player.plane_x * game->player.speed;
	double newposy = game->player.pos_y + game->player.plane_y * game->player.speed;
	double margin = 0.2;

	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx + game->player.plane_x * margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy + game->player.plane_y * margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void move_left(t_game *game)
{
	double newposx = game->player.pos_x - game->player.plane_x * game->player.speed;
	double newposy = game->player.pos_y - game->player.plane_y * game->player.speed;
	double margin = 0.2;

	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx - game->player.plane_x * margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy - game->player.plane_y * margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void rotate_player(t_player *player, double angle)
{
	double old_dir_x = player->dir_x;
	double old_plane_x = player->plane_x;

	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void key_hook(mlx_key_data_t keydata, void *params)
{
	(void)keydata;
	(void)params;
}

void main_hook(void *params)
{
	t_game *game = (t_game *)params;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)) rotate_player(&game->player, game->player.rotate_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)) rotate_player(&game->player, -game->player.rotate_speed);

	raycast_frame(game);
}

char *map_data[] = {
	"111111111111111111111111",
	"100000000011000000000001",
	"101100000111000000000001",
	"100100000000000000000001",
	"111111111011000001110001",
	"100000000011000001110111",
	"111101111111110111000001",
	"111101111111110111010001",
	"100000000000000000000001",
	"111111111111111111111111",
	NULL
};

int main(void)
{
	t_game game;
	int i;

	game.map.map_h = 10;
	game.map.map_w = 24;
	game.map.map_array = malloc(sizeof(char *) * (game.map.map_h + 1));
	if (!game.map.map_array) { perror("malloc"); return 1; }
	i = 0;
	while (map_data[i]) { game.map.map_array[i] = map_data[i]; i++; }
	game.map.map_array[i] = NULL;

	game.mlx = mlx_init(WIN_W, WIN_H, "cub3D - MLX42 Textured", false);
	if (!game.mlx) { fprintf(stderr, "MLX init failed\n"); return 1; }

	game.textures.north = mlx_load_png("textures/cerezo.png");
	game.textures.south = mlx_load_png("textures/champi.png");
	game.textures.west  = mlx_load_png("textures/limonagrio.png");
	game.textures.east  = mlx_load_png("textures/planta.png");

	if (!game.textures.north || !game.textures.south || !game.textures.west || !game.textures.east)
	{
		fprintf(stderr, "Error: could not load all textures\n");
		if (game.textures.north) mlx_delete_texture(game.textures.north);
		if (game.textures.south) mlx_delete_texture(game.textures.south);
		if (game.textures.west)  mlx_delete_texture(game.textures.west);
		if (game.textures.east)  mlx_delete_texture(game.textures.east);
		mlx_terminate(game.mlx);
		free(game.map.map_array);
		return 1;
	}

	game.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	if (!game.img) { fprintf(stderr, "Error creating image\n"); return 1; }
	mlx_image_to_window(game.mlx, game.img, 0, 0);

	game.player.pos_x = 3.5;
	game.player.pos_y = 3.5;
	game.player.dir_x = -1.0;
	game.player.dir_y = 0.0;
	game.player.plane_x = 0.0;
	game.player.plane_y = 0.866;
	game.player.speed = 0.3;
	game.player.rotate_speed = 0.08;

	game.wall_tex.tex = NULL;
	game.wall_tex.tex_x = 0;
	game.wall_tex.tex_y = 0;
	game.wall_tex.tex_pos = 0.0;
	game.wall_tex.tex_step = 0.0;

	game.raycast.hit = 0;

	mlx_loop_hook(game.mlx, main_hook, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);

	if (game.img) mlx_delete_image(game.mlx, game.img);
	if (game.textures.north) mlx_delete_texture(game.textures.north);
	if (game.textures.south) mlx_delete_texture(game.textures.south);
	if (game.textures.west)  mlx_delete_texture(game.textures.west);
	if (game.textures.east)  mlx_delete_texture(game.textures.east);
	mlx_terminate(game.mlx);
	free(game.map.map_array);

	return 0;
}
