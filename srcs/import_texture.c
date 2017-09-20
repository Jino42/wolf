/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:12:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/20 22:26:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		import_texture(t_env *e)
{
	int		fd;

	if (!(e->text = ft_memalloc(TEXT_X * TEXT_Y * 4)))
		return (0);
	if (!(fd = open("fichier.img", O_RDONLY)))
		return (0);
	if ((read(fd, e->text, TEXT_X * TEXT_Y * 4)) != TEXT_X * TEXT_Y * 4)
		return (0);
	if (!(e->skybox = ft_memalloc(1920 * 1200 * 4)))
		return (0);
	if (!(fd = open("skybox", O_RDONLY)))
		return (0);
	if ((read(fd, e->skybox, 1920 * 1200 * 4)) != 1920 * 1200 * 4)
		return (0);
	return (1);
}
