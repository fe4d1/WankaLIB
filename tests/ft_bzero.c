#include "check.h"

/* zeroes exactly n bytes, nothing outside */
int	main(void)
{
	char	a[12];
	int		n;

	memset(a, 'x', 12);
	ft_bzero(a + 1, 10);
	// the x on both sides catch a write one byte too far or too early
	T("zeroes n bytes and no more", !memcmp(a, "x\0\0\0\0\0\0\0\0\0\0x", 12));
	memset(a, 'x', 12);
	ft_bzero(a, 0);
	// n 0 must not touch memory at all
	T("n 0 writes nothing", a[0] == 'x');
	n = -1;
	ft_bzero(&n, sizeof(n));
	// bzero takes void pointer so it must work on any type not only char
	T("works on an int", n == 0);
	return (t_end());
}
