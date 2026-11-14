#include "check.h"

int	main(void)
{
	T("equal", ft_memcmp("abc", "abc", 3) == 0);
	T("s1 smaller", ft_memcmp("abc", "abd", 3) < 0);
	T("s1 bigger", ft_memcmp("abd", "abc", 3) > 0);
	T("difference after n", ft_memcmp("abc", "abd", 2) == 0);
	T("n 0", ft_memcmp("abc", "xyz", 0) == 0);
	T("does not stop at \\0", ft_memcmp("ab\0x", "ab\0y", 4) < 0);
	T("compares as unsigned char", ft_memcmp("\200", "\0", 1) > 0);
	T("compares as unsigned char 2", ft_memcmp("a", "\377", 1) < 0);
	return (t_end());
}
