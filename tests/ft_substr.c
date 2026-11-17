#include "check.h"
#include <stdlib.h>

/* at most len chars from start, empty if start is past the end */
int	main(void)
{
	char	*s;

	// len chars from start
	TS("middle", ft_substr("hello world", 6, 5), "world");
	// start 0
	TS("from the start", ft_substr("hello", 0, 3), "hel");
	// the whole string
	TS("whole string", ft_substr("hello", 0, 5), "hello");
	// len is a maximum, it stops at the end of s
	TS("len bigger than what is left", ft_substr("hello", 2, 100), "llo");
	// len 0 gives an empty string and not NULL
	TS("len 0", ft_substr("hello", 1, 0), "");
	// start at the terminator gives an empty string
	TS("start is the length", ft_substr("hello", 5, 3), "");
	// start after the end must not read there, it gives an empty string
	TS("start after the end", ft_substr("hello", 100, 3), "");
	// an empty s gives an empty string
	TS("empty string", ft_substr("", 0, 5), "");
	// the last char only
	TS("last char", ft_substr("hello", 4, 1), "o");
	alloc_reset();
	s = ft_substr("hello", 1, 1000000);
	// malloc must use what is left of s and not len
	T("huge len does not allocate more than needed", alloc_max() <= 64);
	free(s);
	// when malloc fails substr must return NULL
	MFAIL("malloc fails", ft_substr("hello", 1, 3), free);
	// the empty result is also a malloc that can fail
	MFAIL("malloc fails with start after the end", ft_substr("hi", 9, 3), free);
	return (t_end());
}
