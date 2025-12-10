/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:34:42 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/02 16:21:32 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (!accum)
		error_exit("Empty .cub file");
	out = ft_split(accum, '\n');
	free(accum);
	return (out);
}
