/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:36:57 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:37:10 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**dup_map(t_data *d)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (d->map_h + 1));
	if (!copy)
		exit(1);
	i = -1;
	while (++i < d->map_h)
		copy[i] = ft_strdup(d->map[i]);
	copy[i] = NULL;
	return (copy);
}
