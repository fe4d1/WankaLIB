#include "check.h"

/* difference as unsigned char, stops at \0 or at n */
int	main(void)
{
	// same strings give 0
	T("equal", ft_strncmp("abc", "abc", 3) == 0);
	// n bigger than the strings must stop at the terminator
	T("equal with big n", ft_strncmp("abc", "abc", 100) == 0);
	// only the sign of the result matters, not the exact value
	T("s1 smaller", ft_strncmp("abc", "abd", 3) < 0);
	// and the other way round
	T("s1 bigger", ft_strncmp("abd", "abc", 3) > 0);
	// a difference after the first n chars does not count
	T("difference after n", ft_strncmp("abc", "abd", 2) == 0);
	// n 0 compares nothing so it is equal
	T("n 0", ft_strncmp("abc", "xyz", 0) == 0);
	// the terminator of s1 is smaller than c
	T("s1 shorter", ft_strncmp("ab", "abc", 3) < 0);
	// c is bigger than the terminator of s2
	T("s2 shorter", ft_strncmp("abc", "ab", 3) > 0);
	// unlike memcmp it stops at the terminator even if n is bigger
	T("stops at \\0", ft_strncmp("abc\0x", "abc\0y", 5) == 0);
	// two empty strings are equal
	T("empty strings", ft_strncmp("", "", 5) == 0);
	// empty is smaller than anything
	T("empty vs not empty", ft_strncmp("", "a", 1) < 0);
	// 128 is negative as char, as unsigned char it is bigger than 0
	T("compares as unsigned char", ft_strncmp("\200", "\0", 1) > 0);
	// 255 must be bigger than a, as signed char it would be -1
	T("compares as unsigned char 2", ft_strncmp("a", "\377", 1) < 0);
	return (t_end());
}
