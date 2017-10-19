/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:49:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 23:34:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int 	verif_player(t_env *e)
{
	int y;
	int x;
	int incr;

	y = 0;
	incr = 0;
	while (y < e->map.len_y)
	{
		x = 0;
		while (x < e->map.len_x)
		{
			if (e->map.map[y][x] == 'x')
				incr++;
			if (!ft_isin("012345xB", e->map.map[y][x]))
				return (end_of_program(e, "Probleme d'indication de block\n"));
			x++;
		}
		y++;
	}
	if (incr != 1)
		return (end_of_program(e, "Probleme joueur\n"));
	return (1);
}

static int	verif_border(t_env *e)
{
	int y;
	int x;

	y = 0;
	while (y < e->map.len_y)
	{
		if (e->map.map[y][0] != '1' && e->map.map[y][e->map.len_x - 1])
			return (end_of_program(e, "Petit coquin va !\n"));
		y++;
	}
	x = 0;
	while (x < e->map.len_x)
	{
		if (e->map.map[0][x] != '1' && e->map.map[e->map.len_y - 1][x])
			return (end_of_program(e, "Petit coquin va !\n"));
		x++;
	}
	return (1);
}

static int	add_line(t_env *e, char **line)
{
	int i;

	if (e->map.len_y && !(e->map.len_y % SIZE_REALLOC_MAP))
		if (!(e->map.map = (char **)ft_memrealloc((void *)e->map.map,
		sizeof(char **) * e->map.len_y, sizeof(char **) *
		e->map.len_y + sizeof(char **) * SIZE_REALLOC_MAP)))
			return (end_of_program(e, "Realloc error\n"));
	i = -1;
	e->map.map[e->map.len_y] = *line;
	e->map.len_x = ft_max(e->map.len_x, ft_strlen(*line));
	*line = NULL;
	e->map.len_y++;
	return (1);
}

int			init_map(t_env *e, char *path_map)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(path_map, O_RDONLY);
	line = NULL;
	if (!fd)
		return (ft_ret_error("Erreur de fichier\n"));
	if (!(e->map.map = ft_memalloc(sizeof(char **) * SIZE_REALLOC_MAP)))
		return (end_of_program(e, "Malencontreuse mallocationnage\n"));
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (line)
		{
			if (!add_line(e, &line))
				return (end_of_program(e, "ERROR\n"));
		}
	}
	if (ret == -1)
		return (end_of_program(e, "Erreur de fichier\n"));
	if (!verif_border(e) || !verif_player(e))
		return (0);
	return (1);
}
