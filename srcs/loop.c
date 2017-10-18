/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/18 23:30:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**Glissement sur MUR ! Car deux etape
*/

static void	update_fps(t_env *e, t_fps *fps)
{
	gettimeofday(&fps->step2, NULL);
	if (e->s)
	{
		e->time_frame = (float)(fps->step2.tv_usec - fps->cur.tv_usec) / 1000000;
		if (e->time_frame < 0.005)
			e->time_frame = 0.005;
		if (fps->cur.tv_sec != fps->step2.tv_sec)
			e->time_frame = (float)(fps->step2.tv_usec + (1000000 - fps->cur.tv_usec)) / 1000000;
	}
	gettimeofday(&fps->cur, NULL);
	if (fps->cur.tv_sec - fps->step.tv_sec)
	{
		fps->ret_fps = fps->fps;
		ft_printf("FPS [%i]\n", fps->ret_fps);
		fps->fps = 0;
		gettimeofday(&fps->step, NULL);
		e->s++;
	}
	fps->fps++;
}

void		update_sprite_position(t_env *e, t_player *player)
{
	t_sprite	*sprite;
	t_list		*lst;
	int			i;

	i = 0;
	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		sprite->rela.x = sprite->pos.x - player->pos.x;
		sprite->rela.y = sprite->pos.y - player->pos.y;
		sprite->spe_angle = (int)(atan2f(sprite->rela.y, sprite->rela.x) * 300);
		sprite->hit = 0;
		i++;
		lst = lst->next;
	}
}

/*
** Vector target ?
** By the tip, what do we do ?
*/

void		fvector2d_limit(t_fvector2d *a, const float limit)
{
	if (fvector2d_magnitude(*a) > limit)
	{
		fvector2d_normalize(a);
		a->x *= limit;
		a->y *= limit;
	}
	return ;
}

void		vec_test(t_env *e)
{
	t_list *lst;
	t_sprite *sprite;
	float	speed;

	t_fvector2d temp;
	speed = 2;
	t_fvector2d dist;
	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		if (e->flag & SP_GRAVITY)
		{
			dist.x = e->player.pos.x - sprite->pos.x;
			dist.y = e->player.pos.y - sprite->pos.y;
			if (dist.x && dist.y)
			{
				sprite->acceleration.x = fvector2d_normalized(dist).x * 0.2;
				sprite->acceleration.y = fvector2d_normalized(dist).y * 0.2;
				sprite->velocity.x += sprite->acceleration.x;
				sprite->velocity.y += sprite->acceleration.y;
			}
			else
			{
				sprite->velocity.x = 0.01;
				sprite->velocity.y = 0.01;
			}
		}
		fvector2d_limit(&sprite->velocity, 3);
		temp.x = sprite->pos.x + sprite->velocity.x * e->time_frame;
		temp.y = sprite->pos.y + sprite->velocity.y * e->time_frame;

		if ((int)sprite->pos.x < e->map.len_x &&
			(int)sprite->pos.y < e->map.len_y)
		{
			if (e->map.map[(int)sprite->pos.y][(int)temp.x] == B_VOID)
				sprite->pos.x = temp.x;
			else
				sprite->velocity.x = -sprite->velocity.x;
			if (e->map.map[(int)temp.y][(int)sprite->pos.x] == B_VOID)
				sprite->pos.y = temp.y;
			else
				sprite->velocity.y = -sprite->velocity.y;
		}
		lst = lst->next;
	}
}

void 		wolf_free_btree(void *item)
{
	(void)item;
	return ;
}

int			loop(t_env *e)
{
	if (!(e->flag & F_3D))
		ft_bzero(e->img->data, e->width * e->height * 4);
	ft_bzero(e->apply, sizeof(int) * (WIN_WIDTH + 10));
	ft_bzero(e->ray_end, sizeof(t_fvector2d) * (WIN_WIDTH + 10));
	update_fps(e, &e->fps);
	update_key_event(e);
	update_sprite_position(e, &e->player);
	raycast_wolf(e, &e->player);
	/*t_list *lst;

	lst = e->sprite;
	while (lst)
	{
		sprite_wolf(e, lst->content);
		lst = lst->next;
	}*/
	if (e->sprite_aff)
	{
		btree_env_apply_infix(e, e->sprite_aff, &sprite_wolf);
		btree_apply_free(e->sprite_aff, &wolf_free_btree);
		e->sprite_aff = NULL;
	}
	radar(e);
	vec_test(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
