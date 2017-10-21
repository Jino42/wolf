/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:55:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/21 21:10:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		*raycast_wolf_part(void *ptr)
{
	t_ptr_env		*p;
	float			cam;
	t_ray			ray;

	p = ptr;
	ft_bzero(&ray, sizeof(t_ray));
	while (p->start < p->end)
	{
		ray.x_screen = (int)p->start;
		cam = (p->start * 2) / p->e->width - 1;
		raycast(&ray, &p->e->map,
			fvector2d_construct(p->player->pos.x, p->player->pos.y),
			fvector2d_construct(p->player->dir.x + p->player->plan.x * cam,
								p->player->dir.y + p->player->plan.y * cam));
		if (p->e->flag & F_3D)
			raycast_aff(p->e, &ray, p->start);
		p->e->ray_end[(int)p->start] = ray.end;
		p->e->dist[(int)p->start] = ray.dist_wall;
		sprite_hit(p, p->e, &ray, p->start);
		p->start++;
	}
	pthread_exit(NULL);
	return (NULL);
}

void			raycast_wolf(t_env *e, t_player *player)
{
	t_ptr_env	p[NB_THREAD];
	pthread_t	t[NB_THREAD];
	int			i;
	int			col_per_th;

	pthread_mutex_init(&e->mutex, NULL);
	col_per_th = e->width / NB_THREAD;
	i = 0;
	while (i < NB_THREAD)
	{
		p[i].player = player;
		p[i].e = e;
		p[i].nb = i + 1;
		p[i].start = i * col_per_th;
		p[i].end = p[i].start + col_per_th;
		pthread_create(&t[i], NULL, raycast_wolf_part, (void *)&p[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&e->mutex);
}
