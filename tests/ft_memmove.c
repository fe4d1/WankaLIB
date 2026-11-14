#include "check.h"

int	main(void)
{
	char	b[11];
	char	d[5];

	strcpy(b, "0123456789");
	T("returns dst", ft_memmove(b + 2, b, 5) == b + 2);
	T("overlap with dst after src", !strcmp(b, "0101234789"));
	strcpy(b, "0123456789");
	ft_memmove(b, b + 2, 5);
	T("overlap with dst before src", !strcmp(b, "2345656789"));
	strcpy(b, "0123456789");
	ft_memmove(b + 1, b, 9);
	T("overlap shifted by one", !strcmp(b, "0012345678"));
	strcpy(b, "0123456789");
	ft_memmove(b, b, 10);
	T("same pointer", !strcmp(b, "0123456789"));
	ft_memmove(b + 3, b, 0);
	T("len 0 writes nothing", !strcmp(b, "0123456789"));
	memset(d, 'x', 5);
	ft_memmove(d + 1, "a\0b", 3);
	T("no overlap and does not stop at \\0", !memcmp(d, "xa\0bx", 5));
	T("NULL NULL 0", ft_memmove(NULL, NULL, 0) == NULL);
	T("NULL NULL 3 (other testers expect NULL and no crash)",
		ft_memmove(NULL, NULL, 3) == NULL);
	return (t_end());
}
