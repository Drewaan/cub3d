/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:11:58 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/01 20:12:00 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	**read_file_to_array(char *path)
{
	int		fd;
	char	*line;
	char	*accum;
	char	**out;
	char	*tmp;

	accum = NULL;
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
