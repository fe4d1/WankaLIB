#include "check.h"

/* no empty words, NULL at the end, frees everything if a malloc fails */
int	main(void)
{
	// the normal case, the array ends with NULL
	TT("three words", ft_split("hello big world", ' '), "hello", "big",
		"world");
	// delimiters together must not make empty words
	TT("several delimiters in a row", ft_split("a,,b,,,c", ','), "a", "b", "c");
	// delimiters at the start and the end must not make empty words
	TT("delimiters at both ends", ft_split("  hello  world  ", ' '), "hello",
		"world");
	// no delimiter gives one word, the whole string
	TT("no delimiter", ft_split("hello", ' '), "hello");
	// no word gives an array with only NULL, not NULL itself
	TT("only delimiters", ft_split("     ", ' '), NULL);
	// same for an empty string
	TT("empty string", ft_split("", ' '), NULL);
	// words of one char catch an off by one in the word length
	TT("one char words", ft_split("a b c d", ' '), "a", "b", "c", "d");
	// the terminator is never a delimiter inside the string
	TT("delimiter is \\0", ft_split("hello", '\0'), "hello");
	// empty string with c 0 is still no word
	TT("empty string and delimiter \\0", ft_split("", '\0'), NULL);
	// word count must not count the delimiter before
	TT("one word with delimiter before", ft_split(" a", ' '), "a");
	// word count must not count the delimiter after
	TT("one word with delimiter after", ft_split("a ", ' '), "a");
	// only c is a delimiter, other spaces belong to the word
	TT("tab as delimiter", ft_split("a\tb c", '\t'), "a", "b c");
	// when one malloc fails every word made before must be freed and NULL
	// returned, valgrind shows the leaks
	MFAIL("malloc fails (every word and the array)",
		ft_split("aa bb cc dd", ' '), t_tabfree);
	// even with no word the array malloc can fail
	MFAIL("malloc fails with no words", ft_split("   ", ' '), t_tabfree);
	return (t_end());
}
