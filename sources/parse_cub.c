/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:52:41 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 17:30:16 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int  count_lines(int fd)
{
    int     n = 0;
    char    *line;

    while ((line = get_next_line(fd)))
    {
        n++;
        free(line);
    }
    return (n);
}

static char	**read_file_lines(const char *file)
{
	 int     fd;
    int     total;
    char    **arr;
    char    *line;
    int     i;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (NULL);

    total = count_lines(fd);
    close(fd);

    arr = malloc(sizeof(char *) * (total + 1));
    if (!arr)
        return (NULL);

    fd = open(file, O_RDONLY);
    i = 0;
    while ((line = get_next_line(fd)))
    {
        arr[i] = ft_strtrim(line, "\n");
        free(line);
        i++;
    }
    arr[i] = NULL;
    close(fd);
    return (arr);
}

static int is_config_line(char *s)
{
    if (!s || !*s)
        return (0);

    return (
        !ft_strncmp(s, "NO ", 3) ||
        !ft_strncmp(s, "SO ", 3) ||
        !ft_strncmp(s, "WE ", 3) ||
        !ft_strncmp(s, "EA ", 3) ||
        !ft_strncmp(s, "F ", 2)  ||
        !ft_strncmp(s, "C ", 2)
    );
}

static int parse_config_block(t_game *g, char **lines, int *i)
{
    int configs = 0;

    while (lines[*i] && configs < 6)
    {
        if (is_config_line(lines[*i]))
        {
            if (!ft_strncmp(lines[*i], "NO ", 3) || !ft_strncmp(lines[*i], "SO ", 3)
                || !ft_strncmp(lines[*i], "WE ", 3) || !ft_strncmp(lines[*i], "EA ", 3))
            {
                if (parse_textures(g, lines[*i]))
                    return (1);
            }
            else if (!ft_strncmp(lines[*i], "F ", 2) || !ft_strncmp(lines[*i], "C ", 2))
            {
                if (parse_colors(g, lines[*i]))
                    return (1);
            }
            configs++;
        }
        (*i)++;
    }
    return (configs == 6 ? 0 : 1);
}

int parse_cub(t_game *game, const char *file)
{
    char    **lines;
    int     i;

    lines = read_file_lines(file);
    if (!lines)
        return (1);
    i = 0;
    if (parse_config_block(game, lines, &i))
    {
        ft_free_split(lines);
        return (1);
    }
    while (lines[i] && lines[i][0] == '\0')
        i++;
    if (parse_map(game, lines, &i))
    {
        ft_free_split(lines);
        return (1);
    }
    if (validate_map(&game->map))
    {
        ft_free_split(lines);
        return (1);
    }
    ft_free_split(lines);
    return (0);
}
