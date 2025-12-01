#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

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

// API
void		parser_init(t_parser *p);
void		parse_file(t_parser *p, char *path);
void		parse_color(t_color *c, char *s);
void		load_map_parser(t_parser *p, char **lines);
void		check_map_parser(t_parser *p);

char		**read_file_to_array(char *path);
char		**dup_map(t_parser *p);
void		free_split(char **s);
void		free_parser(t_parser *p);

void		data_to_game(t_parser *p, t_game *g);

#endif