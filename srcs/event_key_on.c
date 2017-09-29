/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/23 16:00:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53 || keycode == 65307)//
		exit(end_of_program(e, NULL));
	if (keycode)
		e->key[keycode] = 1;
	if (keycode == 6 || keycode == 99)//
		e->flag & F_AFF_BASIC ? (e->flag ^= F_AFF_BASIC) :
								(e->flag |= F_AFF_BASIC);
	if (keycode == 7 || keycode == 120)
	{
		e->flag & F_3D ? (e->flag ^= F_3D) : (e->flag |= F_3D);
		if (e->flag & F_3D)
			e->radar.lt = e->radar.len_tile;
		else
			e->radar.lt = e->radar.len_tile_fs;
	}
	if (keycode == 92)
	{
		ft_printf("Size ; %i\n", e->rez);
		e->rez <<= 1;
	}
	if (keycode == 88)
		e->rez >>= 1;
	return (1);
}
