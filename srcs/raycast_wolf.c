/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/01 16:59:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

typedef struct		s_ptr_env
{
	t_env 			*e;
	t_player		*player;
	float			start;
	float			end;
	int				nb;
}					t_ptr_env;

void	raycast_wolf_aff_2d(t_env *e, t_player *player,
		t_ray *ray, int lt)
{
	t_pxtopx to;

	to.x1 = player->pos.x * lt;
	to.y1 = player->pos.y * lt;
	to.x2 = ray->end.x * lt;
	to.y2 = ray->end.y * lt;
	mlxji_draw_line(e->img, &to, COL_RED_SMOOTH);
}

void		*raycast_wolf_part(void *ptr)
{
	t_ptr_env *p;
	t_fvector2d	ray_dir;
	t_fvector2d	ray_start;
	float		cam;
	float		s_screen;
	t_ray		ray;

	p = ptr;
	ft_bzero(&ray, sizeof(t_ray));
	s_screen = p->start;
	while (s_screen < p->end)
	{
		cam = (s_screen * 2) / p->player->len_screen - 1; //inter [-1 1]
		ray_dir.x = p->player->dir.x + p->player->plan.x * cam;
		ray_dir.y = p->player->dir.y + p->player->plan.y * cam;
		ray_start.x = p->player->pos.x;
		ray_start.y = p->player->pos.y;
		(void)p->e->map;

		raycast(&ray, &p->e->map, ray_start, ray_dir);
		raycast_wolf_aff_2d(p->e, p->player, &ray, p->e->radar.lt);
		p->e->dist[(int)s_screen] = p->e->ray.dist_wall;
		if (p->e->flag & F_3D)
			raycast_wolf_aff_3d(p->e, &ray, s_screen);
//		sprite_hit(p->e, &ray, s_screen);	
//		MUTEX
		s_screen++;
	}
	pthread_exit(NULL);
	return (NULL);
}

void		raycast_wolf(t_env *e, t_player *player)
{
	t_ptr_env	p[NB_THREAD];
	pthread_t	t[NB_THREAD];
	int			i;
	int			col_per_th;

	col_per_th = player->len_screen / NB_THREAD;
	i = 0;
	while (i < NB_THREAD)
	{
		p[i].player = player;
		p[i].e = e;
		p[i].nb = i + 1;
		p[i].start = i * col_per_th;
		p[i].end = p[i].start + col_per_th;
		pthread_create (&t[i], NULL, raycast_wolf_part, (void *)&p[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}
