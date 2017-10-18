/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 19:03:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/18 23:31:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		draw_map(t_env *e, int len_tile)
{
	int			x;
	int			y;

	y = 0;
	while (y < e->map.len_y)
	{
		x = 0;
		while (x < e->map.len_x)
		{
			if (e->map.map[y][x] != '0')
			{
				e->to.x1 = x * len_tile;
				e->to.x2 = e->to.x1 + len_tile;
				e->to.y1 = y * len_tile;
				e->to.y2 = e->to.y1 + len_tile;
				if (e->to.x1 < e->width &&
					e->to.y1 < e->height)
					mlxji_draw_case(e->img, &e->to, COL_MAP_2D);
			}
			x++;
		}
		y++;
	}
}

static void		draw_fov(t_env *e, t_player *player, int len_tile)
{
	e->to.x1 = (player->pos.x) * len_tile;
	e->to.y1 = (player->pos.y) * len_tile;
	e->to.x2 = (player->pos.x + player->dir.x + player->plan.x) * len_tile;
	e->to.y2 = (player->pos.y + player->dir.y + player->plan.y) * len_tile;
	mlxji_draw_line(e->img, &e->to, COL_GREEN_CLEAR);
	e->to.x1 = (player->pos.x) * len_tile;
	e->to.y1 = (player->pos.y) * len_tile;
	e->to.x2 = (player->pos.x + player->dir.x - player->plan.x) * len_tile;
	e->to.y2 = (player->pos.y + player->dir.y - player->plan.y) * len_tile;
	mlxji_draw_line(e->img, &e->to, COL_GREEN_CLEAR);
}

static void		draw_vector_on_player(t_env *e, t_fvector2d *vec, int len_tile, int col)
{
	e->to.x1 = e->player.pos.x * len_tile;
	e->to.y1 = e->player.pos.y * len_tile;
	e->to.x2 = (e->player.pos.x + vec->x) * len_tile;
	e->to.y2 = (e->player.pos.y + vec->y) * len_tile;
	mlxji_draw_line(e->img, &e->to, col);
}

static void		draw_pos_player(t_env *e, t_player *player, int len_tile)
{
	int		coef;
	float	range_player;

	range_player = len_tile / 5;
	coef = len_tile * (player->pos.x - (int)player->pos.x);
	e->to.x1 = (int)player->pos.x * len_tile + coef - range_player;
	e->to.x2 = (int)player->pos.x * len_tile + coef + range_player;
	coef = len_tile * ((player->pos.y - (int)player->pos.y));
	e->to.y1 = (int)player->pos.y * len_tile + coef - range_player;
	e->to.y2 = (int)player->pos.y * len_tile + coef + range_player;
	mlxji_draw_case(e->img, &e->to, COL_PLAYER_2D);
}

static void		draw_sprite(t_env *e, t_sprite *sprite, int len_tile)
{
	int		coef;
	float	range_player;

	range_player = len_tile >> 3;
	coef = len_tile * (sprite->pos.x - (int)sprite->pos.x);
	e->to.x1 = (int)sprite->pos.x * len_tile + coef - range_player;
	e->to.x2 = (int)sprite->pos.x * len_tile + coef + range_player;
	coef = len_tile * ((sprite->pos.y - (int)sprite->pos.y));
	e->to.y1 = (int)sprite->pos.y * len_tile + coef - range_player;
	e->to.y2 = (int)sprite->pos.y * len_tile + coef + range_player;
	mlxji_draw_case(e->img, &e->to, COL_EN_2D);
}

void			radar(t_env *e)
{
	t_radar *radar;
	int		i;

	radar = &e->radar;
	draw_map(e, radar->lt);
	draw_pos_player(e, &e->player, radar->lt);
	draw_fov(e, &e->player, radar->lt);
	draw_vector_on_player(e, &e->player.dir, radar->lt, 0x70F188);
	i = 0;
	t_list *lst;

	lst = e->sprite;
	while (lst)
	{
		draw_sprite(e, lst->content, radar->lt);
		i++;
		lst = lst->next;
	}
}
