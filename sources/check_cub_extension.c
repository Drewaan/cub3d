/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_extension.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:08:39 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 16:08:41 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_cub_extension(const char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (!ft_strncmp(file + len - 4, ".cub", 4));
}
