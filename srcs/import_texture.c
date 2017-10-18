/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:12:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/18 23:03:33 by ntoniolo         ###   ########.fr       */
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
	read(fd, &e->tex_sprite[itex].width, sizeof(int));
	read(fd, &e->tex_sprite[itex].height, sizeof(int));
	size_tex = e->tex_sprite[itex].width * e->tex_sprite[itex].height * 4;
	ft_printf("%i %i _ %i\n", size_tex, e->tex_sprite[itex].width, e->tex_sprite[itex].width);
	//e->tex_sprite[itex].len_min = ft_min(e->tex_sprite[itex].width, e->tex_sprite[itex].height);
	if (itex && (e->tex_sprite[itex].width > TEX_MAX ||
			e->tex_sprite[itex].width > TEX_MAX ||
			e->tex_sprite[itex].height < 0 || e->tex_sprite[itex].height < 0))
		return (0);
	if (!(e->tex_sprite[itex].tex = ft_memalloc(size_tex)))
		return (0);
	if ((read(fd, e->tex_sprite[itex].tex, size_tex)) != size_tex)
		return (0);
	return (1);
}

int		import_texture(t_env *e)
{
	if (!(import(e, 0, "tex/skybox")))
		return (0);
	if (!(import(e, 1, "tex/wall_herbe.img")))
		return (0);
	if (!(import(e, 2, "tex/wall.img")))
		return (0);
	if (!(import(e, 3, "tex/wall_stone.img")))
		return (0);
	if (!(import(e, 4, "tex/wall_stone_plant.img")))
		return (0);
	if (!(import(e, 5, "tex/wall_brick.img")))
		return (0);
	//import sprite
	temp(e, 0, "tex/potato.img");
	temp(e, 1, "tex/prevo.img");
	return (1);
}
