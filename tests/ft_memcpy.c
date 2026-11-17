#include "check.h"

/* copies exactly n raw bytes, returns dst */
int	main(void)
{
	char	d[10];
	int		src[3];
	int		dst[3];

	memset(d, 'x', 10);
	// memcpy returns the original dst, not dst + n
	T("returns dst", ft_memcpy(d + 1, "abcd", 4) == d + 1);
	// the x around catch a byte written too far or too early
	T("copies n bytes and no more", !memcmp(d, "xabcdxxxxx", 10));
	// n 0 still returns dst
	T("n 0 returns dst", ft_memcpy(d, "zzz", 0) == d);
	// and does not write
	T("n 0 writes nothing", d[0] == 'x');
	ft_memcpy(d, "a\0b", 3);
	// memcpy copies bytes, a zero byte is not the end
	T("does not stop at \\0", !memcmp(d, "a\0b", 3));
	src[0] = 1;
	src[1] = -2;
	src[2] = INT_MAX;
	ft_memcpy(dst, src, sizeof(src));
	// void pointer means any type, n is in bytes not in elements
	T("works on ints", !memcmp(dst, src, sizeof(src)));
	// nothing to copy so nothing is read and dst NULL is returned
	T("NULL NULL 0", ft_memcpy(NULL, NULL, 0) == NULL);
	// libc crashes here, most 42 testers expect a check that returns NULL
	T("NULL NULL 3 (other testers expect NULL and no crash)",
		ft_memcpy(NULL, NULL, 3) == NULL);
	return (t_end());
}
