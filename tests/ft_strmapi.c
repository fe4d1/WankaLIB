#include "check.h"
#include <stdlib.h>

static char	add_index(unsigned int i, char c)
{
	return (c + i);
}

static char	upper(unsigned int i, char c)
{
	(void)i;
	return (toupper(c));
}

int	main(void)
{
	const char	*s = "hello";
	char		*r;

	TS("index is passed to f", ft_strmapi("aaaa", add_index), "abcd");
	TS("f applied to every char", ft_strmapi("hello", upper), "HELLO");
	TS("empty string", ft_strmapi("", upper), "");
	r = ft_strmapi(s, upper);
	T("returns a new string", r != NULL && r != s);
	T("original is not changed", !strcmp(s, "hello"));
	free(r);
	MFAIL("malloc fails", ft_strmapi("abc", upper), free);
	return (t_end());
}
