/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:31:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 23:05:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		free_map(t_map *map)
{
	int y;

	if (map->map)
	{
		y = 0;
		while (y < map->len_y)
		{
			if (map->map[y])
				ft_strdel(&map->map[y]);
			y++;
		}
		free(map->map);
	}
}

int				end_of_program(t_env *e, char *str)
{
	free_map(&e->map);
	free_lst_sprite(e);
	free_mlx(e);
	free_env(e);
	if (str)
		ft_putstr_fd(str, 2);
	ft_bzero(e, sizeof(t_env));
	return (0);
}
