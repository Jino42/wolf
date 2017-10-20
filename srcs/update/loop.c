/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/20 18:24:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void			wolf_aff_sprite(t_env *e)
{
	if (e->sprite_aff)
	{
		if (e->flag & F_3D && e->nb_sprite < 100)
			btree_env_apply_infix(e, e->sprite_aff, &sprite_wolf);
		free_btree_sprite(e);
	}
}

void  				test(t_env *e)
{
	t_fvector2d s, d, c;

	s.x = e->player.dir.x + e->player.plan.x;
	s.y = e->player.dir.y + e->player.plan.y;
	d.x = e->player.dir.x - e->player.plan.x;
	d.y = e->player.dir.y - e->player.plan.y;
	//printf("At : %f %f %f\n", atan2f(s.y, s.x), atan2f(d.y, d.x), atan2f(s.y, s.x) - atan2f(d.y, d.x));
	if (e->sprite)
	{
		t_sprite *sprite = e->sprite->content;
		c = sprite->rela;
		fvector2d_normalize(&c);
		//c.x -= e->player.dir.x;
		//c.y -= e->player.dir.y;
		fvector2d_normalize(&s);
		fvector2d_normalize(&d);
		float all = atan2f(s.y, s.x) - atan2f(d.y, d.x);
		float new = atan2f(c.y, c.x) - atan2f(d.y, d.x);//atan2f(e->player.dir.y, e->player.dir.x);
		printf ("D %f H %f G %f\n", atan2f(s.y, s.x), atan2f(e->player.dir.y, e->player.dir.x), atan2f(d.y, d.x));
		printf ("_____O %f___\n", atan2f(c.y, c.x));
		printf("So %f / %f | %% %f\n\n", new, all, new/all);
		//printf ("rela : %f\n", atan2f(c.y, c.x));
		//printf ("%% : %f\n", atan2f(c.y, c.x) / (atan2f(s.y, s.x) - atan2f(d.y, d.x)));
	}
}

int					loop(t_env *e)
{
	//
	if (!(e->flag & F_3D))
		ft_bzero(e->img->data, e->width * e->height * 4);
	ft_bzero(e->apply, sizeof(int) * (WIN_WIDTH + 10));
	ft_bzero(e->ray_end, sizeof(t_fvector2d) * (WIN_WIDTH + 10));
	//
	//
	update_fps(e, &e->fps);
	update_key_event(e);
	update_sprite_position(e);
	//
	raycast_wolf(e, &e->player);
	wolf_aff_sprite(e);
	raycast_aff_view_2d(e, &e->player);
	test(e);
	radar(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
