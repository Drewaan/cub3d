#include "../MLX42/include/MLX42/MLX42.h"

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* #define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_game
{
    mlx_t       *mlx;
    mlx_image_t *img;
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
    double oldTime;
} t_game;

static void	draw_vertical_line(mlx_image_t *img, int x, int start, int end, uint32_t color)
{
    if (start < 0) start = 0;
    if (end >= SCREEN_HEIGHT) end = SCREEN_HEIGHT - 1;
    for (int y = start; y <= end; y++)
        mlx_put_pixel(img, x, y, color);
}

static uint32_t make_color(uint8_t r, uint8_t g, uint8_t b)
{
    return (0xFF << 24) | (r << 16) | (g << 8) | b;
}

static void	render(void *param)
{
    t_game *g = (t_game*)param;
    mlx_delete_image(g->mlx, g->img);
    g->img = mlx_new_image(g->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(g->mlx, g->img, 0, 0);

    double frameTime = (mlx_get_time() - g->oldTime);
    g->oldTime = mlx_get_time();

    double moveSpeed = frameTime * 5.0;
    double rotSpeed = frameTime * 3.0;

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = g->dirX + g->planeX * cameraX;
        double rayDirY = g->dirY + g->planeY * cameraX;

        int mapX = (int)g->posX;
        int mapY = (int)g->posY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double sideDistX, sideDistY;
        int stepX, stepY;
        int hit = 0, side = 0;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (g->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - g->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (g->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - g->posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }

        double perpWallDist = (side == 0) ? sideDistX - deltaDistX : sideDistY - deltaDistY;
        if (perpWallDist < 0.0001) perpWallDist = 0.0001;
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

        uint8_t r=255,gc=255,b=0;
        switch(worldMap[mapX][mapY])
        {
            case 1: r=255; gc=0;   b=0;   break;
            case 2: r=0;   gc=255; b=0;   break;
            case 3: r=0;   gc=0;   b=255; break;
            case 4: r=255; gc=255; b=255; break;
            default: r=255; gc=255; b=0;  break;
        }
        if (side == 1) { r /= 2; gc /= 2; b /= 2; }

        draw_vertical_line(g->img, x, drawStart, drawEnd, make_color(r, gc, b));
    }

    // Movimiento y rotación (teclas)
    if (mlx_is_key_down(g->mlx, MLX_KEY_UP))
    {
        if (worldMap[(int)(g->posX + g->dirX * moveSpeed)][(int)g->posY] == 0)
            g->posX += g->dirX * moveSpeed;
        if (worldMap[(int)g->posX][(int)(g->posY + g->dirY * moveSpeed)] == 0)
            g->posY += g->dirY * moveSpeed;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_DOWN))
    {
        if (worldMap[(int)(g->posX - g->dirX * moveSpeed)][(int)g->posY] == 0)
            g->posX -= g->dirX * moveSpeed;
        if (worldMap[(int)g->posX][(int)(g->posY - g->dirY * moveSpeed)] == 0)
            g->posY -= g->dirY * moveSpeed;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
    {
        double oldDirX = g->dirX;
        g->dirX = g->dirX * cos(-rotSpeed) - g->dirY * sin(-rotSpeed);
        g->dirY = oldDirX * sin(-rotSpeed) + g->dirY * cos(-rotSpeed);
        double oldPlaneX = g->planeX;
        g->planeX = g->planeX * cos(-rotSpeed) - g->planeY * sin(-rotSpeed);
        g->planeY = oldPlaneX * sin(-rotSpeed) + g->planeY * cos(-rotSpeed);
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
    {
        double oldDirX = g->dirX;
        g->dirX = g->dirX * cos(rotSpeed) - g->dirY * sin(rotSpeed);
        g->dirY = oldDirX * sin(rotSpeed) + g->dirY * cos(rotSpeed);
        double oldPlaneX = g->planeX;
        g->planeX = g->planeX * cos(rotSpeed) - g->planeY * sin(rotSpeed);
        g->planeY = oldPlaneX * sin(rotSpeed) + g->planeY * cos(rotSpeed);
    }
}

int main(void)
{
    t_game g;

    g.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster (MLX42)", false);
    if (!g.mlx)
        return (fprintf(stderr, "Error inicializando MLX42\n"), EXIT_FAILURE);

    g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(g.mlx, g.img, 0, 0);

    g.posX = 22.0; g.posY = 12.0;
    g.dirX = -1.0; g.dirY = 0.0;
    g.planeX = 0.0; g.planeY = 0.66;
    g.oldTime = mlx_get_time();

    mlx_loop_hook(g.mlx, &render, &g);
    mlx_loop(g.mlx);

    mlx_terminate(g.mlx);
    return 0;
} */

void ray_refresh(t_ray *ray, t_player *player, int x)
{
	ray->hit = 0;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->camera = 2 * x / (double)WIN_W - 1.0;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera;
	/* cálculo seguro de delta_dist: evita divisiones por 0 */
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
	int max_y = game->map.win_h;
	int max_x = game->map.win_w;

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
		/* verificación de límites del mapa */
		if (game->raycast.map_x < 0 || game->raycast.map_x >= max_x
			|| game->raycast.map_y < 0 || game->raycast.map_y >= max_y)
		{
			game->raycast.hit = 1; /* fuera del mapa -> interrumpir */
			break;
		}
		/* mapa: '1' son paredes */
		if (game->map.map_array[game->raycast.map_y][game->raycast.map_x] == '1')
			game->raycast.hit = 1;
	}
}

/* Usamos la forma segura: perpWallDist = sideDist - deltaDist */
void set_dist(t_game *game)
{
	if (game->raycast.side_hit == 0)
		game->raycast.wall_dist = game->raycast.side_dist_x - game->raycast.delta_dist_x;
	else
		game->raycast.wall_dist = game->raycast.side_dist_y - game->raycast.delta_dist_y;

	/* evitar distancias 0 o negativas */
	if (game->raycast.wall_dist <= 0.0001)
		game->raycast.wall_dist = 0.0001;

	/* calcular el punto exacto de impacto (para texturizado si se desea) */
	if (game->raycast.side_hit == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.wall_dist * game->raycast.ray_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.wall_dist * game->raycast.ray_x;
	/* wall_x en [0,1) */
	game->raycast.wall_x -= floor(game->raycast.wall_x);
}

/* ----------------- dibujo ----------------- */

static inline uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

void draw_vertical_line(mlx_image_t *img, int x, int start, int end, uint32_t color)
{
	if (x < 0 || x >= WIN_W) return;
	if (start < 0) start = 0;
	if (end >= WIN_H) end = WIN_H - 1;
	for (int y = start; y <= end; ++y)
		mlx_put_pixel(img, x, y, color);
}

/* ----------------- raycast principal ----------------- */

void raycast_frame(t_game *game)
{
	int x;

	/* recreamos la imagen cada frame (simple) */
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	mlx_image_to_window(game->mlx, game->img, 0, 0);

	/* fondo (césped/ceiling) opcional: aquí suelo oscuro y techo claro */
	for (int y = 0; y < WIN_H / 2; ++y) {
		for (int x2 = 0; x2 < WIN_W; ++x2)
			mlx_put_pixel(game->img, x2, y, rgba(120, 180, 255, 255)); /* cielo */
	}
	for (int y = WIN_H/2; y < WIN_H; ++y) {
		for (int x2 = 0; x2 < WIN_W; ++x2)
			mlx_put_pixel(game->img, x2, y, rgba(80, 80, 80, 255)); /* suelo */
	}

	x = 0;
	while (x < WIN_W)
	{
		ray_refresh(&game->raycast, &game->player, x);
		ray_dir(&game->raycast, &game->player);
		check_hit(game);
		set_dist(game);

		int line_height = (int)(WIN_H / game->raycast.wall_dist);
		int draw_start = -line_height / 2 + WIN_H / 2;
		int draw_end = line_height / 2 + WIN_H / 2;

		/* elegir color según side y mapa (puedes extender por tipo de muro) */
		uint32_t color;
		char tile = '0';
		if (game->raycast.map_x >= 0 && game->raycast.map_x < game->map.win_w
			&& game->raycast.map_y >= 0 && game->raycast.map_y < game->map.win_h)
			tile = game->map.map_array[game->raycast.map_y][game->raycast.map_x];

		switch (tile)
		{
			case '1': color = rgba(200, 40, 40, 255); break; /* rojo */
			default:  color = rgba(220, 220, 220, 255); break;
		}
		if (game->raycast.side_hit == 1) {
			/* oscurecer para dar profundidad */
			uint8_t r = (color >> 16) & 0xFF;
			uint8_t g = (color >> 8) & 0xFF;
			uint8_t b = color & 0xFF;
			color = rgba(r/2, g/2, b/2, 255);
		}

		draw_vertical_line(game->img, x, draw_start, draw_end, color);
		x++;
	}
}

/* ----------------- mapa de prueba y main ----------------- */

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

	/* cargar mapa */
	game.map.win_h = 10; /* filas */
	game.map.win_w = 24; /* columnas */
	game.map.map_array = malloc(sizeof(char *) * (game.map.win_h + 1));
	if (!game.map.map_array) return perror("malloc"), 1;
	i = 0;
	while (map_data[i]) {
		game.map.map_array[i] = map_data[i];
		i++;
	}
	game.map.map_array[i] = NULL;

	/* init MLX */
	game.mlx = mlx_init(WIN_W, WIN_H, "Raycaster MLX42 - FIXED", false);
	if (!game.mlx) {
		fprintf(stderr, "Error inicializando MLX42\n");
		return 1;
	}
	game.img = NULL;

	/* colocar al jugador dentro del mapa */
	game.player.pos_x = 3.5;   /* dentro del área abierta */
	game.player.pos_y = 3.5;
	game.player.dir_x = -1.0;
	game.player.dir_y = 0.0;
	game.player.plane_x = 0.0;
	game.player.plane_y = 0.66;
	game.player.speed = 5.0;
	game.player.rotate_speed = 3.0;

	/* loop hook: siempre que mlx ejecute el loop, llamamos a render */
	mlx_loop_hook(game.mlx, (void *)raycast_frame, &game);
	mlx_loop(game.mlx);

	/* cleanup */
	if (game.img) mlx_delete_image(game.mlx, game.img);
	mlx_terminate(game.mlx);
	free(game.map.map_array);
	return 0;
}

