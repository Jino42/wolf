/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/20 15:53:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	cac_sprite(t_env *e)
{
	t_list		*lst;
	t_sprite	*sprite;

	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		sprite->pos = e->player.pos;
		lst = lst->next;
	}
}

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(end_of_program(e, NULL));
	if (keycode)
		e->key[keycode] = 1;
	if (keycode == 6)
		e->flag & F_AFF_BASIC ? (e->flag ^= F_AFF_BASIC) :
								(e->flag |= F_AFF_BASIC);
	if (keycode == 7)
	{
		e->flag & F_3D ? (e->flag ^= F_3D) : (e->flag |= F_3D);
		e->radar.lt = (e->flag & F_3D ? e->radar.len_tile :
										e->radar.len_tile_fs);
	}
	if (keycode == 18)
		e->flag & SP_GRAVITY ? (e->flag ^= SP_GRAVITY) :
										(e->flag |= SP_GRAVITY);
	if (keycode == 42)
		free_lst_sprite(e);
	if (keycode == 30)
		cac_sprite(e);
	return (1);
}
