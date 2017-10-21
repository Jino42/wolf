/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:12:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 22:44:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	import_tex(t_tex *tex, int itex, char *path)
{
	int		fd;
	int		size_tex;

	if (!(fd = open(path, O_RDONLY)))
		return (0);
	read(fd, &tex[itex].width, sizeof(int));
	read(fd, &tex[itex].height, sizeof(int));
	size_tex = tex[itex].width * tex[itex].height * 4;
	if (itex && (tex[itex].width > TEX_MAX ||
				tex[itex].height > TEX_MAX ||
				tex[itex].height < 0 || tex[itex].width < 0))
		return (0);
	if (!(tex[itex].tex = ft_memalloc(size_tex)))
		return (0);
	if ((read(fd, tex[itex].tex, size_tex)) != size_tex)
		return (0);
	return (1);
}

int			import_texture(t_env *e)
{
	if (!(import_tex(e->tex, 0, "tex/skybox")))
		return (0);
	if (!(import_tex(e->tex, 1, "tex/wall_herbe.img")))
		return (0);
	if (!(import_tex(e->tex, 2, "tex/wall.img")))
		return (0);
	if (!(import_tex(e->tex, 3, "tex/wall_stone.img")))
		return (0);
	if (!(import_tex(e->tex, 4, "tex/wall_stone_plant.img")))
		return (0);
	if (!(import_tex(e->tex, 5, "tex/wall_brick.img")))
		return (0);
	if (!(import_tex(e->tex_sprite, 0, "tex/potato.img")))
		return (0);
	if (!(import_tex(e->tex_sprite, 1, "tex/prevo.img")))
		return (0);
	return (1);
}
