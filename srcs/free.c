#include "wolf.h"

void		free_lst_sprite(t_env *e)
{
	t_list *lst;
	t_list *tmp;

	lst = e->sprite;
	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	e->sprite = NULL;
	e->nb_sprite = 0;
}

static void	wolf_free_btree(void *item)
{
	(void)item;
	return ;
}

void		free_btree_sprite(t_env *e)
{
	btree_apply_free(e->sprite_aff, &wolf_free_btree);
	e->sprite_aff = NULL;
}

void		free_env(t_env *e)
{
	int i;

	i = 0;
	while (i < NB_TEX)
	{
		ft_strdel((void *)&e->tex[i].tex);
		i++;
	}
}

void		free_mlx(t_env *e)
{
	if (!e || !e->img)
		return ;
	if (e->mlx && e->img)
		mlx_destroy_image(e->mlx, e->img->img);
	if (e->mlx && e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e->img)
		free(e->img);
}
