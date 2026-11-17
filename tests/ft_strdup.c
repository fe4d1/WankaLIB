#include "check.h"
#include <stdlib.h>

/* new copy of the exact size (len + 1), NULL if malloc fails */
int	main(void)
{
	const char	*s = "hello";
	char		*d;

	d = ft_strdup(s);
	// a copy in new memory, returning s is not a copy
	T("new pointer", d != NULL && d != s);
	// same chars and terminated
	TS("same content", d, "hello");
	// an empty string still needs one byte for the terminator
	TS("empty", ft_strdup(""), "");
	// copies up to the first zero byte
	TS("stops at \\0", ft_strdup("ab\0cd"), "ab");
	alloc_reset();
	d = ft_strdup("abc");
	// exactly strlen plus one byte for the terminator, not more or less
	T("allocates length + 1", alloc_max() == 4);
	free(d);
	// when malloc fails strdup must return NULL and not write in it
	MFAIL("malloc fails", ft_strdup("abc"), free);
	return (t_end());
}
