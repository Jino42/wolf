/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:12:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/20 17:34:37 by ntoniolo         ###   ########.fr       */
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
	return (1);
}
