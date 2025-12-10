/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:39:30 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 18:36:57 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	is_ident(char *l)
{
	return (!ft_strncmp(l, "NO ", 3) || !ft_strncmp(l, "SO ", 3)
		|| !ft_strncmp(l, "WE ", 3) || !ft_strncmp(l, "EA ", 3)
		|| !ft_strncmp(l, "F ", 2) || !ft_strncmp(l, "C ", 2));
}

int	is_empty_line(char *ln)
{
	int	i;

	if (!ln || !*ln)
		return (1);
	i = 0;
	while (ln[i])
	{
		if (ln[i] != ' ' && ln[i] != '\t' && ln[i] != '\n' && ln[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
