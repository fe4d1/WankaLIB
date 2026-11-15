#include "check.h"
#include <stdlib.h>

/* removes the set chars from both ends only */
int	main(void)
{
	TS("both ends", ft_strtrim("  hello  ", " "), "hello");
	TS("several chars in set", ft_strtrim("xyhelloyx", "xy"), "hello");
	TS("keeps set chars in the middle", ft_strtrim("xxhexxlloxx", "x"),
		"hexxllo");
	TS("only the start", ft_strtrim("--abc", "-"), "abc");
	TS("only the end", ft_strtrim("abc--", "-"), "abc");
	TS("nothing to trim", ft_strtrim("abc", "xyz"), "abc");
	TS("everything trimmed", ft_strtrim("xxxx", "x"), "");
	TS("empty s1", ft_strtrim("", "abc"), "");
	TS("empty set", ft_strtrim("  abc  ", ""), "  abc  ");
	TS("both empty", ft_strtrim("", ""), "");
	TS("one char left", ft_strtrim("  a  ", " "), "a");
	MFAIL("malloc fails", ft_strtrim("  abc  ", " "), free);
	MFAIL("malloc fails when everything is trimmed", ft_strtrim("xx", "x"),
		free);
	return (t_end());
}
