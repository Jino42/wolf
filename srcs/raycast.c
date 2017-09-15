/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:53:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/15 17:01:54 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	test(t_env *e)
{
	int x;
	double cam;
	double ray_dir_x;
	double ray_dir_y;
	double len_x;
	double len_y;
	int len_screen;
	t_player *player;

	player = &e->player;
	len_screen = 320;
	x = 0;
	while (x < len_screen)
	{
		cam = 2 * x / len_screen - 1; //inter [-1 1]
		ray_dir_x = player->dir_x + player->plan_x * cam;
		ray_dir_y = player->dir_y + player->plan_y * cam;

		//need len per [x] and [y]
		len_x = sqrt(1+(pow(ray_dir_y, 2) / pow(ray_dir_x, 2)));
		len_y = sqrt(1+(pow(ray_dir_x, 2) / pow(ray_dir_y, 2)));
		printf("%.3f %.3f\n", ); ///////TROUVER DISTANCE !!!!!!!!!!!!
		exit(0);
		//printf("%.3f %.3f\n", len_y, len_x);
		x++;
	}
}
