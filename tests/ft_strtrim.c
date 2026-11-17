#include "check.h"
#include <stdlib.h>

/* removes the set chars from both ends only */
int	main(void)
{
	// set chars go away from the start and the end
	TS("both ends", ft_strtrim("  hello  ", " "), "hello");
	// set is a list of chars, not a word, any order
	TS("several chars in set", ft_strtrim("xyhelloyx", "xy"), "hello");
	// only the ends are trimmed, the middle stays
	TS("keeps set chars in the middle", ft_strtrim("xxhexxlloxx", "x"),
		"hexxllo");
	// nothing at the end to trim
	TS("only the start", ft_strtrim("--abc", "-"), "abc");
	// nothing at the start to trim
	TS("only the end", ft_strtrim("abc--", "-"), "abc");
	// nothing to trim gives a copy
	TS("nothing to trim", ft_strtrim("abc", "xyz"), "abc");
	// start and end cross, the result is an empty string and not NULL
	TS("everything trimmed", ft_strtrim("xxxx", "x"), "");
	// an empty s1 gives an empty string
	TS("empty s1", ft_strtrim("", "abc"), "");
	// an empty set trims nothing
	TS("empty set", ft_strtrim("  abc  ", ""), "  abc  ");
	// both empty
	TS("both empty", ft_strtrim("", ""), "");
	// catches an off by one when only one char is left
	TS("one char left", ft_strtrim("  a  ", " "), "a");
	// when malloc fails strtrim must return NULL
	MFAIL("malloc fails", ft_strtrim("  abc  ", " "), free);
	// the empty result is also a malloc that can fail
	MFAIL("malloc fails when everything is trimmed", ft_strtrim("xx", "x"),
		free);
	return (t_end());
}
