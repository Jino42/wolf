/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/26 21:43:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		print_map(t_env *e)
{
	int i;

	ft_printf("_____________________________\n");
	i = 0;
	while (i < e->map.len_y)
	{
		ft_printf("%s\n", e->map.map[i]);
		i++;
	}
	ft_printf("_____________________________\n\n");
}

int			main(int argc, char **argv)
{
	t_env e;

	if (argc != 2)
		return (ft_ret_error("Miss Args\n"));
	init_env(&e);
	if (!(init_map(&e, argv[1])))
		return (0);
	print_map(&e);
	init_var(&e);
	//temp
	e.sprite[0].pos.x = 6.5;
	e.sprite[0].pos.y = 4.1;
	e.wall.x = 6.5;
	e.wall.y = 4.1;
	e.endw.x = 7.5;
	e.endw.y = 8.1;
	ft_printf("Bef\n");
	if (!(import_texture(&e)))
		return (ft_ret_error("Erreur de textures\n")); //free	
	ft_printf("Aff\n");
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	return (0);
}
