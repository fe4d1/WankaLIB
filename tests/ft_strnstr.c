#include "check.h"

/* the needle must fit entirely in the first len bytes */
int	main(void)
{
	const char	*h = "lorem ipsum dolor";

	// returns a pointer to where the needle starts
	T("found", ft_strnstr(h, "ipsum", 17) == h + 6);
	// a match at index 0
	T("found at the start", ft_strnstr(h, "lorem", 17) == h);
	// a match that ends right before the terminator
	T("found at the end", ft_strnstr(h, "dolor", 17) == h + 12);
	// len bigger than the string must stop at the terminator
	T("len bigger than the string", ft_strnstr(h, "dolor", 100) == h + 12);
	// a needle longer than what is left is not found
	T("not found", ft_strnstr(h, "dolorx", 100) == NULL);
	// the last char of the needle is the last byte inside len
	T("needle ends exactly at len", ft_strnstr(h, "ipsum", 11) == h + 6);
	// the needle starts inside len but ends one byte after, not found
	T("needle ends one after len", ft_strnstr(h, "ipsum", 10) == NULL);
	// the man page says an empty needle returns haystack
	T("empty needle returns haystack", ft_strnstr(h, "", 17) == h);
	// even with len 0
	T("empty needle and len 0", ft_strnstr(h, "", 0) == h);
	// len 0 searches nothing
	T("len 0", ft_strnstr(h, "lorem", 0) == NULL);
	// must not read past the end of the haystack
	T("needle longer than haystack", ft_strnstr("abc", "abcd", 10) == NULL);
	// nothing to find in an empty haystack
	T("empty haystack", ft_strnstr("", "a", 5) == NULL);
	h = "aaab";
	// a partial match at 0 fails, the real one starts at 1
	// skipping the chars of the failed try misses it
	T("partial match then real match", ft_strnstr(h, "aab", 4) == h + 1);
	h = "abcabd";
	// after abc fails the search goes on from the next start
	T("restarts after a failed match", ft_strnstr(h, "abd", 6) == h + 3);
	// a needle of one char at the last position
	T("one char needle", ft_strnstr(h, "d", 6) == h + 5);
	return (t_end());
}
