/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:49:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/21 22:57:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	add_line(t_env *e, char **line)
{
	if (e->map.len_y && !(e->map.len_y % SIZE_REALLOC_MAP))
		e->map.map = (char **)ft_memrealloc((void *)e->map.map,
		sizeof(char **) * e->map.len_y, sizeof(char **) *
		e->map.len_y + sizeof(char **) * SIZE_REALLOC_MAP);
	e->map.map[e->map.len_y] = *line;
	e->map.len_x = ft_max(e->map.len_x, ft_strlen(*line));
	*line = NULL;
	e->map.len_y++;
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
		return (0);
	while ((ret = get_next_line(fd, &line)) == 1)
		if (line)
			add_line(e, &line);
	if (ret == -1)
		return (ft_ret_error("Erreur de fichier\n")); //End Of Prog
	return (1);
}
