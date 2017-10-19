#include "wolf.h"

void	raycast_aff_basic(t_env *e, int nb_cast, int start_y, int end_y)
{
	t_pxtopx to;

	ft_bzero(&to, sizeof(t_pxtopx));
	if (end_y >= e->size_side)
		end_y = e->size_side - 1;
	if (start_y < 0)
		start_y = 0;
	to.x1 = (nb_cast + 1);
	to.y1 = start_y;
	to.x2 = (nb_cast + 1);
	to.y2 = end_y;
	mlxji_draw_y_line(e->img, &to, COL_GREEN_SMOOTH);
}
