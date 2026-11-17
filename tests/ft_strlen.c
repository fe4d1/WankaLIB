#include "check.h"

/* counts bytes up to the first \0 */
int	main(void)
{
	char	big[2001];

	memset(big, 'a', 2000);
	big[2000] = '\0';
	// the terminator is not counted
	T("empty", ft_strlen("") == 0);
	// catches a count that starts at 1
	T("one char", ft_strlen("a") == 1);
	// a normal string
	T("hello", ft_strlen("hello") == 5);
	// stops at the first zero byte
	T("stops at first \\0", ft_strlen("ab\0cd") == 2);
	// bytes above 127 are negative as char but they are not the end
	T("chars above 127", ft_strlen("\xff\x80\x01") == 3);
	// long string, catches a counter that is too small
	T("2000 chars", ft_strlen(big) == 2000);
	return (t_end());
}
