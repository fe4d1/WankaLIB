#include "check.h"

int	main(void)
{
	const char	*s = "hello world";

	T("last of several", ft_strrchr(s, 'o') == s + 7);
	T("only one", ft_strrchr(s, 'h') == s);
	T("last char", ft_strrchr(s, 'd') == s + 10);
	T("not found", ft_strrchr(s, 'z') == NULL);
	T("\\0 returns a pointer to the terminator", ft_strrchr(s, '\0') == s + 11);
	T("c is converted to char (o + 256)", ft_strrchr(s, 'o' + 256) == s + 7);
	T("empty string", ft_strrchr("", 'a') == NULL);
	s = "";
	T("empty string and \\0", ft_strrchr(s, '\0') == s);
	s = "aaaa";
	T("all the same", ft_strrchr(s, 'a') == s + 3);
	return (t_end());
}
