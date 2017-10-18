/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/18 23:26:15 by ntoniolo         ###   ########.fr       */
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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void	raycast_wolf_aff_2d(t_env *e, t_player *player, int lt, int i)
{
	t_pxtopx to;

	to.x1 = player->pos.x * lt;
	to.y1 = player->pos.y * lt;
	to.x2 = e->ray_end[i].x * lt;
	to.y2 = e->ray_end[i].y * lt;
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

		raycast(&ray, &p->e->map, ray_start, ray_dir);
		p->e->dist[(int)s_screen] = ray.dist_wall;
		if (p->e->flag & F_3D)
			raycast_wolf_aff_3d(p->e, &ray, s_screen);
//		raycast_wolf_aff_2d(p->e, p->player, &ray, p->e->radar.lt);
		p->e->ray_end[(int)s_screen] = ray.end;
		pthread_mutex_lock (&mutex);
		sprite_hit(p->e, &ray, s_screen);
		pthread_mutex_unlock (&mutex);
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

	pthread_mutex_init(&mutex, NULL);
	col_per_th = player->len_screen / NB_THREAD;
	i = 0;
	while (i < NB_THREAD)
	{
		p[i].player = player;
		p[i].e = e;
		p[i].nb = i + 1;
		p[i].start = i * col_per_th;
		p[i].end = p[i].start + col_per_th ;
		pthread_create (&t[i], NULL, raycast_wolf_part, (void *)&p[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	for (int i = 0; i < e->width; i++)
		raycast_wolf_aff_2d(e, &e->player, e->radar.lt, i);
}
