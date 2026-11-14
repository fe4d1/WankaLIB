#include "check.h"
#include <stdlib.h>

int	main(void)
{
	TS("two words", ft_strjoin("hello ", "world"), "hello world");
	TS("empty s1", ft_strjoin("", "abc"), "abc");
	TS("empty s2", ft_strjoin("abc", ""), "abc");
	TS("both empty", ft_strjoin("", ""), "");
	TS("one char each", ft_strjoin("a", "b"), "ab");
	MFAIL("malloc fails", ft_strjoin("abc", "def"), free);
	return (t_end());
}
