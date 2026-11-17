#include "check.h"

/* first match, c used as a char, \0 can be found */
int	main(void)
{
	const char	*s = "hello world";

	// the first char of the string
	T("first char", ft_strchr(s, 'h') == s);
	// strchr gives the first one, not the last
	T("first of several", ft_strchr(s, 'o') == s + 4);
	// the last char before the terminator
	T("last char", ft_strchr(s, 'd') == s + 10);
	// no match gives NULL
	T("not found", ft_strchr(s, 'z') == NULL);
	// the terminator is part of the string, a loop while s[i] misses it
	T("\\0 returns a pointer to the terminator", ft_strchr(s, '\0') == s + 11);
	// c is an int but it is compared as a char, 367 becomes o
	T("c is converted to char (o + 256)", ft_strchr(s, 'o' + 256) == s + 4);
	// nothing to find in an empty string
	T("empty string", ft_strchr("", 'a') == NULL);
	s = "";
	// the terminator of an empty string is its first byte
	T("empty string and \\0", ft_strchr(s, '\0') == s);
	return (t_end());
}
