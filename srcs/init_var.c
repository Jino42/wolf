/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:46:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/23 15:40:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->height = WIN_HEIGHT;
	e->width = WIN_WIDTH;
	e->size_side = e->height;
	e->size_half_side = e->height / 2;
	e->flag |= F_3D;
	e->rez = (1 << 6) ;
}

static void	init_radar(t_env *e, t_radar *radar)
{
	radar->len_tile = ft_max(e->width, e->height) / 8;
	radar->len_tile_fs = ft_min(e->width, e->height);
	radar->len_tile /= ft_max(e->map.len_x, e->map.len_y);
	radar->len_tile_fs /= ft_min(e->map.len_x, e->map.len_y);
	radar->len_x = radar->len_tile * e->map.len_x;
	radar->len_y = radar->len_tile * e->map.len_y;
	radar->lt = radar->len_tile;
}

static void	init_player(t_env *e, t_player *player)
{
	(void)e;
	player->pos.x = 3.2;
	player->pos.y = 4.1;
	player->move_speed = 0.05;
	player->rotate_speed = 0.04;
	player->dir.x = 1;
	player->plan.y = 0.66;
	player->len_screen = e->width;
}

static void	init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->img = mlxji_new_img(e->mlx, e->width, e->height);
	if (!e->img)
		exit(ft_ret_error("Img non cree\n"));
	e->win = mlx_new_window(e->mlx, e->width, e->height, "Wolf3d");
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, &event_key_on, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, &event_key_off, e);
}

void		init_var(t_env *e)
{
	init_player(e, &e->player);
	init_radar(e, &e->radar);
	init_mlx(e);
}
