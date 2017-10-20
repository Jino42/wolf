/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 19:36:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/10/20 19:04:30 by ntoniolo         ###   ########.fr       */
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
float			cmp_dist2(void *item, void *insert)
{
	return (((t_sprite *)insert)->dist - ((t_sprite *)item)->dist);
}

void  				test(t_env *e)
{

	/*
		dist = save ray per x_screen//////////////////
		////////////////////////////////////////////
		/////////////////////////////////////////
		/////////////////////////////////////////
		/////////////////////////////////////////
		/////////////////////////////////////////
		/////////////////////////////////////////
		/////////////////////////////////////////
	*/
	t_list *lst;
	t_btree		*ret;
	t_sprite *sprite;
	float all;
	float new;

	all = atan2f(e->player.right.y, e->player.right.x) - atan2f(e->player.left.y, e->player.left.x);
	lst = e->sprite;
	while (lst)
	{
		sprite = lst->content;
		sprite->dir = sprite->rela;
		new = atan2f(sprite->dir.y, sprite->dir.x) - atan2f(e->player.left.y, e->player.left.x);
		float save = all - new;
		new /= all;
		sprite->dist = fvector2d_magnitude(sprite->rela);
		printf("Magnitude : %f\n", sprite->dist);
		sprite->col = new * cos(save) * e->width;
		if (sprite->col >= 0 && sprite->col < e->width)
			sprite->hit = 1;
		fvector2d_normalize(&sprite->dir);
		if (!(ret = btree_create_leaf(sprite)))
			exit(end_of_program(e, "Leaf doesnt create\n"));
		btree_finsert_infix_data(&e->sprite_aff, ret->content, &cmp_dist2);
		lst = lst->next;
	}
}

static void 		update_vector(t_player *player)
{
	player->right.x = player->dir.x + player->plan.x;
	player->right.y = player->dir.y + player->plan.y;
	player->left.x = player->dir.x - player->plan.x;
	player->left.y = player->dir.y - player->plan.y;
	fvector2d_normalize(&player->left);
	fvector2d_normalize(&player->right);
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
	update_vector(&e->player);
	update_fps(e, &e->fps);
	update_key_event(e);
	update_sprite_position(e);
	//
	raycast_wolf(e, &e->player);
	test(e);
	wolf_aff_sprite(e);
	raycast_aff_view_2d(e, &e->player);
	radar(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
