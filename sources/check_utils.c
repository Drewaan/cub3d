/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:40:44 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/10/17 16:54:46 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_args(int argc, char**argv)
{
	char	*tmp;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error: invalid arguments number", 2);
		return (0);
	}
	tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (tmp == NULL)
	{
		ft_putendl_fd("Error: invalid map", 2);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: invalid archive format", 2);
		close(fd);
		return (0);
	}
	close (fd);
	return (1);
}
