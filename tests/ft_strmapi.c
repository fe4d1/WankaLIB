#include "check.h"
#include <stdlib.h>

/* returns the char plus its index */
static char	add_index(unsigned int i, char c)
{
	return (c + i);
}

/* returns the char in uppercase */
static char	upper(unsigned int i, char c)
{
	(void)i;
	return (toupper(c));
}

/* new string made of f(i, c), original untouched */
int	main(void)
{
	const char	*s = "hello";
	char		*r;

	// f gets 0 1 2 3 as index, aaaa becomes abcd
	TS("index is passed to f", ft_strmapi("aaaa", add_index), "abcd");
	// f is applied to every char and the result is terminated
	TS("f applied to every char", ft_strmapi("hello", upper), "HELLO");
	// an empty string gives an empty string and not NULL
	TS("empty string", ft_strmapi("", upper), "");
	r = ft_strmapi(s, upper);
	// strmapi makes a new string, it does not return s
	T("returns a new string", r != NULL && r != s);
	// the original stays as it was
	T("original is not changed", !strcmp(s, "hello"));
	free(r);
	// when malloc fails strmapi must return NULL
	MFAIL("malloc fails", ft_strmapi("abc", upper), free);
	return (t_end());
}
