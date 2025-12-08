/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:54:22 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 16:07:31 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_config(t_game *game, char **lines, int *i)
{
	while (lines[*i] && lines[*i][0])
	{
		if (ft_strncmp(lines[*i], "NO ", 3) == 0
			|| ft_strncmp(lines[*i], "SO ", 3) == 0
			|| ft_strncmp(lines[*i], "WE ", 3) == 0
			|| ft_strncmp(lines[*i], "EA ", 3) == 0)
		{
			if (parse_textures(game, lines[*i]))
				return (1);
		}
		else if (ft_strncmp(lines[*i], "F ", 2) == 0
			|| ft_strncmp(lines[*i], "C ", 2) == 0)
		{
			if (parse_colors(game, lines[*i]))
				return (1);
		}
		else
			break ;
		(*i)++;
	}
	return (0);
}
