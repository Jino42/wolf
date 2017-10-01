/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:12:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/30 15:56:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	import(t_env *e, int itex, char *path)
{
	int		fd;
	int		size_tex;

	if (!(fd = open(path, O_RDONLY)))
		return (0);
	read(fd, &e->tex[itex].width, sizeof(int));
	read(fd, &e->tex[itex].height, sizeof(int));
	size_tex = e->tex[itex].width * e->tex[itex].height * 4;
	ft_printf("%i %i _ %i\n", size_tex, e->tex[itex].width, e->tex[itex].height);
	if (itex && (e->tex[itex].width > TEX_MAX ||
			e->tex[itex].height > TEX_MAX ||
			e->tex[itex].height < 0 || e->tex[itex].width < 0))
		return (0);
	if (!(e->tex[itex].tex = ft_memalloc(size_tex)))
		return (0);
	if ((read(fd, e->tex[itex].tex, size_tex)) != size_tex)
		return (0);
	return (1);
}

static int	temp(t_env *e, int itex, char *path)
{
	int		fd;
	int		size_tex;

	if (!(fd = open(path, O_RDONLY)))
		return (0);
	read(fd, &e->sprite[itex].len_x, sizeof(int));
	read(fd, &e->sprite[itex].len_y, sizeof(int));
	size_tex = e->sprite[itex].len_x * e->sprite[itex].len_y * 4;
	ft_printf("%i %i _ %i\n", size_tex, e->sprite[itex].len_x, e->sprite[itex].len_x);
	e->sprite[itex].len_min = ft_min(e->sprite[itex].len_x, e->sprite[itex].len_y);
	if (itex && (e->sprite[itex].len_x > TEX_MAX ||
			e->sprite[itex].len_x > TEX_MAX ||
			e->sprite[itex].len_y < 0 || e->sprite[itex].len_y < 0))
		return (0);
	if (!(e->sprite[itex].sprite = ft_memalloc(size_tex)))
		return (0);
	if ((read(fd, e->sprite[itex].sprite, size_tex)) != size_tex)
		return (0);
	return (1);
}

int		import_texture(t_env *e)
{
	if (!(import(e, 0, "skybox")))
		return (0);
	if (!(import(e, 1, "wall_herbe.img")))
		return (0);
	//import sprite
	temp(e, 0, "mob.img");
	temp(e, 1, "prevo.img");
	return (1);
}
