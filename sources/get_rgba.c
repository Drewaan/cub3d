/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgba.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:14:27 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 18:14:34 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t    get_rgba(int r, int g, int b, int a)
{
    uint32_t color;

    color = ((uint32_t)r << 24)
          | ((uint32_t)g << 16)
          | ((uint32_t)b << 8)
          | ((uint32_t)a);
    return (color);
}
