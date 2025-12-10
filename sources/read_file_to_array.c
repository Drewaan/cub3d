/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:34:42 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/10 16:57:54 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_lines(char *str)
{
	int	count;
	int	i;

	if (!str || !*str)
		return (0);
	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

static char	*get_line_from_str(char *str, int *pos)
{
	int		start;
	int		len;
	char	*line;

	start = *pos;
	len = 0;
	while (str[*pos] && str[*pos] != '\n')
	{
		len++;
		(*pos)++;
	}
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, str + start, len);
	line[len] = '\0';
	if (str[*pos] == '\n')
		(*pos)++;
	return (line);
}

static char	**split_preserving_empty(char *str)
{
	char	**out;
	int		line_count;
	int		pos;
	int		i;

	if (!str)
		return (NULL);
	line_count = count_lines(str);
	out = malloc(sizeof(char *) * (line_count + 1));
	if (!out)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < line_count && str[pos])
	{
		out[i] = get_line_from_str(str, &pos);
		if (!out[i])
		{
			free_split(out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}

char	**read_file_to_array(char *path)
{
	int		fd;
	char	*line;
	char	*accum;
	char	**out;
	char	*tmp;

	accum = ft_strdup("");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open .cub file");
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(accum, line);
		free(accum);
		accum = tmp;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!accum || !*accum)
		error_exit("Empty .cub file");
	out = split_preserving_empty(accum);
	free(accum);
	return (out);
}
