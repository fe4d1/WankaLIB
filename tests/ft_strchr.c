#include "check.h"

/* first match, c used as a char, \0 can be found */
int	main(void)
{
	const char	*s = "hello world";

	T("first char", ft_strchr(s, 'h') == s);
	T("first of several", ft_strchr(s, 'o') == s + 4);
	T("last char", ft_strchr(s, 'd') == s + 10);
	T("not found", ft_strchr(s, 'z') == NULL);
	T("\\0 returns a pointer to the terminator", ft_strchr(s, '\0') == s + 11);
	T("c is converted to char (o + 256)", ft_strchr(s, 'o' + 256) == s + 4);
	T("empty string", ft_strchr("", 'a') == NULL);
	s = "";
	T("empty string and \\0", ft_strchr(s, '\0') == s);
	return (t_end());
}
