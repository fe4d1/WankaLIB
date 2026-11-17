#include "check.h"

/* last match, c used as a char, \0 can be found */
int	main(void)
{
	const char	*s = "hello world";

	// strrchr gives the last one, not the first
	T("last of several", ft_strrchr(s, 'o') == s + 7);
	// a match at index 0, a loop that stops at i > 0 misses it
	T("only one", ft_strrchr(s, 'h') == s);
	// the last char before the terminator
	T("last char", ft_strrchr(s, 'd') == s + 10);
	// no match gives NULL
	T("not found", ft_strrchr(s, 'z') == NULL);
	// the terminator is part of the string and can be found
	T("\\0 returns a pointer to the terminator", ft_strrchr(s, '\0') == s + 11);
	// c is an int but it is compared as a char, 367 becomes o
	T("c is converted to char (o + 256)", ft_strrchr(s, 'o' + 256) == s + 7);
	// nothing to find in an empty string
	T("empty string", ft_strrchr("", 'a') == NULL);
	s = "";
	// the terminator of an empty string is its first byte
	T("empty string and \\0", ft_strrchr(s, '\0') == s);
	s = "aaaa";
	// every char matches, the last one wins
	T("all the same", ft_strrchr(s, 'a') == s + 3);
	return (t_end());
}
