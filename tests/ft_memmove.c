#include "check.h"

/* copy stays right when src and dst overlap, both directions */
int	main(void)
{
	char	b[11];
	char	d[5];

	strcpy(b, "0123456789");
	// memmove returns the original dst
	T("returns dst", ft_memmove(b + 2, b, 5) == b + 2);
	// dst after src: copying from the start overwrites src before reading
	// it, so this direction must copy from the end
	T("overlap with dst after src", !strcmp(b, "0101234789"));
	strcpy(b, "0123456789");
	ft_memmove(b, b + 2, 5);
	// dst before src: copying from the start is the right way here
	T("overlap with dst before src", !strcmp(b, "2345656789"));
	strcpy(b, "0123456789");
	ft_memmove(b + 1, b, 9);
	// the worst overlap, a forward copy gives 0000000000
	T("overlap shifted by one", !strcmp(b, "0012345678"));
	strcpy(b, "0123456789");
	ft_memmove(b, b, 10);
	// dst and src the same must leave the bytes as they are
	T("same pointer", !strcmp(b, "0123456789"));
	ft_memmove(b + 3, b, 0);
	// len 0 must not write
	T("len 0 writes nothing", !strcmp(b, "0123456789"));
	memset(d, 'x', 5);
	ft_memmove(d + 1, "a\0b", 3);
	// copies bytes, a zero byte is not the end, and no more than len
	T("no overlap and does not stop at \\0", !memcmp(d, "xa\0bx", 5));
	// nothing to copy so dst NULL is returned
	T("NULL NULL 0", ft_memmove(NULL, NULL, 0) == NULL);
	// libc crashes here, most 42 testers expect a check that returns NULL
	T("NULL NULL 3 (other testers expect NULL and no crash)",
		ft_memmove(NULL, NULL, 3) == NULL);
	return (t_end());
}
