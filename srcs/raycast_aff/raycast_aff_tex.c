#include "wolf.h"

void			raycast_aff_tex(t_env *e, int nb_cast,
					int start_y, float len_pp, t_ray *ray)
{
	float		len;
	int			i;
	int			place_x;
	int			icol;
	t_pxtopx to;
	int			tex;

	tex = ray->get - '0';
	ft_bzero(&to, sizeof(t_pxtopx));
	to.x1 = nb_cast + 1;
	to.y2 = start_y;
	place_x = (ray->percent_wall * e->tex[tex].width);
	i = -1;
	len = 0;
	while (++i < ft_min(e->tex[tex].height, e->tex[tex].width))
	{
		to.y1 = to.y2;
		to.y2 = start_y + len;
		if (to.y2 > 0)
		{
			if (to.y1 < 0)
				to.y1 = 0;
			icol = *((int *)&e->tex[tex].tex[(place_x << 2) + i *
					(e->tex[tex].width << 2)]);
			if (to.y2 >= e->size_side)
				to.y2 = e->size_side - 1;
			mlxji_draw_y_line(e->img, &to, icol);
		}
		len += len_pp;
	}
}
