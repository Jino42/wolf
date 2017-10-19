#include "wolf.h"

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
