/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_fire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:45:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/19 20:51:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			create_sprite(t_env *e, t_tex *tex)
{
	t_sprite		sprite;
	t_list			*ret;

	ft_bzero(&sprite, sizeof(t_sprite));
	sprite.len_x = tex->width;
	sprite.len_y = tex->height;
	sprite.len_min = ft_min(tex->height, tex->width);
	sprite.pos = e->player.pos;
	sprite.velocity.x = fvector2d_normalized(e->player.dir).x * 1.5;
	sprite.velocity.y = fvector2d_normalized(e->player.dir).y * 1.5;
	sprite.sprite = tex;
	sprite.dir = e->player.dir;
	if (!(ret = ft_lstnew(&sprite, sizeof(t_sprite))))
		exit(end_of_program(e, NULL));
	ft_lstinsert(&e->sprite, ret);
}

void			event_fire(t_env *e, t_player *player)
{
	(void)player;
	create_sprite(e, &e->tex_sprite[1]);
}
