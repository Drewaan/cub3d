/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:10:48 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:51:42 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check_file.c
#include "../includes/cub3d.h"

void	check_file_extension(char *p)
{
	int	len;

	len = ft_strlen(p);
	if (len < 4 || ft_strncmp(p + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension");
}

static void	check_color_range(int *c)
{
	if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255 || c[2] < 0
		|| c[2] > 255)
		error_exit("Color out of range");
}

void	check_identifiers(t_data *d)
{
	if (!d->paths.no || !d->paths.so || !d->paths.we || !d->paths.ea)
		error_exit("Missing texture path");
	if (!d->floor_color.set || !d->ceil_color.set)
		error_exit("Missing colors");
	check_color_range(d->floor_color.rgb);
	check_color_range(d->ceil_color.rgb);
}
