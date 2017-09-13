/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:25:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 22:07:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->height = WIN_HEIGHT;
	e->width = WIN_WIDTH;
}

void	init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->img = mlxji_new_img(e->mlx, e->width, e->height);
	if (!e->img)
		exit(ft_ret_error("Img non cree\n"));/////////
	e->win = mlx_new_window(e->mlx, e->width, e->height, "Wolf3d");
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, &event_key_on, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, &event_key_off, e);
}

int		init_map(t_env *e, char *path_map)
{
	int fd;
	int ret;
	char *line;

	(void)e;
	fd = open(path_map, O_RDONLY);
	line = NULL;
	if (!fd)
		return (ft_ret_error("Erreur de fichier\n"));
	if (!(e->map = ft_memalloc(sizeof(char **) * SIZE_REALLOC_MAP)))
		return (0);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (line)
		{
			if (e->len_y && !(e->len_y % SIZE_REALLOC_MAP))
				e->map = (char **)ft_memrealloc((void *)e->map, sizeof(char **) * e->len_y, sizeof(char **) * e->len_y + sizeof(char **) * SIZE_REALLOC_MAP);
			e->map[e->len_y] = line;
			line = NULL;
			e->len_y++;
		}
	}
	if (ret == -1)
		return (ft_ret_error("Erreur de fichier\n")); //End Of Prog
	return (1);
}

void		print_map(t_env *e)
{
	int i;

	ft_printf("_____________________________\n");
	i = 0;
	while (i < e->len_y)
	{
		ft_printf("%s\n", e->map[i]);
		i++;
	}
	ft_printf("_____________________________\n\n");
}

int main(int argc, char **argv)
{
	t_env e;

	if (argc != 2)
		return (ft_ret_error("Miss Args\n"));
	init_env(&e);
	if (!(init_map(&e, argv[1])))
		return (0);
	e.pos_x = 3;
	e.pos_y = 4;
	print_map(&e);
	init_mlx(&e);
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	return (0);
}
