#include "check.h"
#include <stdlib.h>

int	main(void)
{
	const char	*s = "hello";
	char		*d;

	d = ft_strdup(s);
	T("new pointer", d != NULL && d != s);
	TS("same content", d, "hello");
	TS("empty", ft_strdup(""), "");
	TS("stops at \\0", ft_strdup("ab\0cd"), "ab");
	alloc_reset();
	d = ft_strdup("abc");
	T("allocates length + 1", alloc_max() == 4);
	free(d);
	MFAIL("malloc fails", ft_strdup("abc"), free);
	return (t_end());
}
