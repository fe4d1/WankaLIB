#include "check.h"
#include <stdlib.h>

static int	all_zero(unsigned char *p, size_t n)
{
	while (n--)
		if (p[n])
			return (0);
	return (1);
}

int	main(void)
{
	unsigned char	*p;
	int				*q;
	void			*z;

	p = malloc(40);
	memset(p, 0xff, 40);
	free(p);
	p = ft_calloc(10, 4);
	T("returns memory", p != NULL);
	T("memory is zeroed", p && all_zero(p, 40));
	free(p);
	q = ft_calloc(5, sizeof(int));
	if (q)
		q[4] = 42;
	T("memory is usable", q && q[4] == 42 && q[0] == 0);
	free(q);
	z = ft_calloc(0, 0);
	T("0 0 returns a pointer for free", z != NULL);
	free(z);
	z = ft_calloc(0, 5);
	T("0 5 returns a pointer for free", z != NULL);
	free(z);
	z = ft_calloc(5, 0);
	T("5 0 returns a pointer for free", z != NULL);
	free(z);
	z = ft_calloc(0, 0);
	p = ft_calloc(0, 0);
	T("0 0 returns a different pointer each time", z != p);
	free(z);
	free(p);
	z = ft_calloc(SIZE_MAX / 2 + 2, 2);
	T("count * size overflow returns NULL", z == NULL);
	free(z);
	MFAIL("malloc fails", ft_calloc(4, 4), free);
	return (t_end());
}
