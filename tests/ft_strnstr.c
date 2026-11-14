#include "check.h"

int	main(void)
{
	const char	*h = "lorem ipsum dolor";

	T("found", ft_strnstr(h, "ipsum", 17) == h + 6);
	T("found at the start", ft_strnstr(h, "lorem", 17) == h);
	T("found at the end", ft_strnstr(h, "dolor", 17) == h + 12);
	T("len bigger than the string", ft_strnstr(h, "dolor", 100) == h + 12);
	T("not found", ft_strnstr(h, "dolorx", 100) == NULL);
	T("needle ends exactly at len", ft_strnstr(h, "ipsum", 11) == h + 6);
	T("needle ends one after len", ft_strnstr(h, "ipsum", 10) == NULL);
	T("empty needle returns haystack", ft_strnstr(h, "", 17) == h);
	T("empty needle and len 0", ft_strnstr(h, "", 0) == h);
	T("len 0", ft_strnstr(h, "lorem", 0) == NULL);
	T("needle longer than haystack", ft_strnstr("abc", "abcd", 10) == NULL);
	T("empty haystack", ft_strnstr("", "a", 5) == NULL);
	h = "aaab";
	T("partial match then real match", ft_strnstr(h, "aab", 4) == h + 1);
	h = "abcabd";
	T("restarts after a failed match", ft_strnstr(h, "abd", 6) == h + 3);
	T("one char needle", ft_strnstr(h, "d", 6) == h + 5);
	return (t_end());
}
