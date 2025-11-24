/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:40:10 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/11/24 19:46:09 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	data_init(t_data *data)
{
	data -> north = NULL;
	data -> south = NULL;
	data -> west = NULL;
	data -> east = NULL;
	data -> floor.red = -1;
	data -> floor.green = -1;
	data -> floor.blue = -1;
	data -> ceiling.red = -1;
	data -> ceiling.green = -1;
	data -> ceiling.blue = -1;
	data -> map_start = 0;
	data -> map_lines = 0;
}
