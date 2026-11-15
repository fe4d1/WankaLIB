#include "check.h"

/* no empty words, NULL at the end, frees everything if a malloc fails */
int	main(void)
{
	TT("three words", ft_split("hello big world", ' '), "hello", "big",
		"world");
	TT("several delimiters in a row", ft_split("a,,b,,,c", ','), "a", "b", "c");
	TT("delimiters at both ends", ft_split("  hello  world  ", ' '), "hello",
		"world");
	TT("no delimiter", ft_split("hello", ' '), "hello");
	TT("only delimiters", ft_split("     ", ' '), NULL);
	TT("empty string", ft_split("", ' '), NULL);
	TT("one char words", ft_split("a b c d", ' '), "a", "b", "c", "d");
	TT("delimiter is \\0", ft_split("hello", '\0'), "hello");
	TT("empty string and delimiter \\0", ft_split("", '\0'), NULL);
	TT("one word with delimiter before", ft_split(" a", ' '), "a");
	TT("one word with delimiter after", ft_split("a ", ' '), "a");
	TT("tab as delimiter", ft_split("a\tb c", '\t'), "a", "b c");
	MFAIL("malloc fails (every word and the array)",
		ft_split("aa bb cc dd", ' '), t_tabfree);
	MFAIL("malloc fails with no words", ft_split("   ", ' '), t_tabfree);
	return (t_end());
}
