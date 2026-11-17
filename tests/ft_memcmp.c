#include "check.h"

/* compares n bytes as unsigned char, does not stop at \0 */
int	main(void)
{
	// same bytes give 0
	T("equal", ft_memcmp("abc", "abc", 3) == 0);
	// only the sign of the result matters, not the exact value
	T("s1 smaller", ft_memcmp("abc", "abd", 3) < 0);
	// and the other way round
	T("s1 bigger", ft_memcmp("abd", "abc", 3) > 0);
	// a difference after the first n bytes does not count
	T("difference after n", ft_memcmp("abc", "abd", 2) == 0);
	// n 0 compares nothing so it is equal
	T("n 0", ft_memcmp("abc", "xyz", 0) == 0);
	// unlike strncmp it keeps going after a zero byte
	T("does not stop at \\0", ft_memcmp("ab\0x", "ab\0y", 4) < 0);
	// 128 is negative as char, as unsigned char it is bigger than 0
	T("compares as unsigned char", ft_memcmp("\200", "\0", 1) > 0);
	// 255 must be bigger than a, as signed char it would be -1
	T("compares as unsigned char 2", ft_memcmp("a", "\377", 1) < 0);
	return (t_end());
}
