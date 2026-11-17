#include "check.h"
#include <stdlib.h>

/* 1 if the n bytes are all zero */
static int	all_zero(unsigned char *p, size_t n)
{
	while (n--)
		if (p[n])
			return (0);
	return (1);
}

/* zeroed memory (heap is dirtied first), size 0, overflow, malloc failure */
int	main(void)
{
	unsigned char	*p;
	int				*q;
	void			*z;

	p = malloc(40);
	memset(p, 0xff, 40);
	free(p);
	p = ft_calloc(10, 4);
	// a normal call must give memory
	T("returns memory", p != NULL);
	// the heap was filled with 0xff before so a missing bzero shows here
	T("memory is zeroed", p && all_zero(p, 40));
	free(p);
	q = ft_calloc(5, sizeof(int));
	if (q)
		q[4] = 42;
	// count times size bytes must be usable up to the last element
	T("memory is usable", q && q[4] == 42 && q[0] == 0);
	free(q);
	z = ft_calloc(0, 0);
	// the subject says size 0 returns a unique pointer that free accepts
	T("0 0 returns a pointer for free", z != NULL);
	free(z);
	z = ft_calloc(0, 5);
	// count 0 is also a total of 0 bytes
	T("0 5 returns a pointer for free", z != NULL);
	free(z);
	z = ft_calloc(5, 0);
	// size 0 is also a total of 0 bytes
	T("5 0 returns a pointer for free", z != NULL);
	free(z);
	z = ft_calloc(0, 0);
	p = ft_calloc(0, 0);
	// unique means two calls never give the same address
	T("0 0 returns a different pointer each time", z != p);
	free(z);
	free(p);
	z = ft_calloc(SIZE_MAX / 2 + 2, 2);
	// count times size overflows size_t so it must return NULL
	// and not a small block that would be written out of bounds
	T("count * size overflow returns NULL", z == NULL);
	free(z);
	// when malloc fails calloc must return NULL and not write in it
	MFAIL("malloc fails", ft_calloc(4, 4), free);
	return (t_end());
}
