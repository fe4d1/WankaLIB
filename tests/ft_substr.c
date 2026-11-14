#include "check.h"
#include <stdlib.h>

int	main(void)
{
	char	*s;

	TS("middle", ft_substr("hello world", 6, 5), "world");
	TS("from the start", ft_substr("hello", 0, 3), "hel");
	TS("whole string", ft_substr("hello", 0, 5), "hello");
	TS("len bigger than what is left", ft_substr("hello", 2, 100), "llo");
	TS("len 0", ft_substr("hello", 1, 0), "");
	TS("start is the length", ft_substr("hello", 5, 3), "");
	TS("start after the end", ft_substr("hello", 100, 3), "");
	TS("empty string", ft_substr("", 0, 5), "");
	TS("last char", ft_substr("hello", 4, 1), "o");
	alloc_reset();
	s = ft_substr("hello", 1, 1000000);
	T("huge len does not allocate more than needed", alloc_max() <= 64);
	free(s);
	MFAIL("malloc fails", ft_substr("hello", 1, 3), free);
	MFAIL("malloc fails with start after the end", ft_substr("hi", 9, 3), free);
	return (t_end());
}
