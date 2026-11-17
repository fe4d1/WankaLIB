#include "check.h"
#include <stdlib.h>

/* new string s1 + s2, empty strings included */
int	main(void)
{
	// s1 then s2 in new memory, terminated
	TS("two words", ft_strjoin("hello ", "world"), "hello world");
	// an empty s1 is still a valid string
	TS("empty s1", ft_strjoin("", "abc"), "abc");
	// an empty s2 is still a valid string
	TS("empty s2", ft_strjoin("abc", ""), "abc");
	// two empty strings give an empty string and not NULL
	TS("both empty", ft_strjoin("", ""), "");
	// the smallest join catches an off by one in the size
	TS("one char each", ft_strjoin("a", "b"), "ab");
	// when malloc fails strjoin must return NULL
	MFAIL("malloc fails", ft_strjoin("abc", "def"), free);
	return (t_end());
}
