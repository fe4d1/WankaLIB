#include "check.h"

int	main(void)
{
	T("equal", ft_strncmp("abc", "abc", 3) == 0);
	T("equal with big n", ft_strncmp("abc", "abc", 100) == 0);
	T("s1 smaller", ft_strncmp("abc", "abd", 3) < 0);
	T("s1 bigger", ft_strncmp("abd", "abc", 3) > 0);
	T("difference after n", ft_strncmp("abc", "abd", 2) == 0);
	T("n 0", ft_strncmp("abc", "xyz", 0) == 0);
	T("s1 shorter", ft_strncmp("ab", "abc", 3) < 0);
	T("s2 shorter", ft_strncmp("abc", "ab", 3) > 0);
	T("stops at \\0", ft_strncmp("abc\0x", "abc\0y", 5) == 0);
	T("empty strings", ft_strncmp("", "", 5) == 0);
	T("empty vs not empty", ft_strncmp("", "a", 1) < 0);
	T("compares as unsigned char", ft_strncmp("\200", "\0", 1) > 0);
	T("compares as unsigned char 2", ft_strncmp("a", "\377", 1) < 0);
	return (t_end());
}
