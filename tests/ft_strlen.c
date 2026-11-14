#include "check.h"

int	main(void)
{
	char	big[2001];

	memset(big, 'a', 2000);
	big[2000] = '\0';
	T("empty", ft_strlen("") == 0);
	T("one char", ft_strlen("a") == 1);
	T("hello", ft_strlen("hello") == 5);
	T("stops at first \\0", ft_strlen("ab\0cd") == 2);
	T("chars above 127", ft_strlen("\xff\x80\x01") == 3);
	T("2000 chars", ft_strlen(big) == 2000);
	return (t_end());
}
