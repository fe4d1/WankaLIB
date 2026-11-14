#include "check.h"

static char	g_d[12];

static char	*set(const char *s)
{
	memset(g_d, 'x', 12);
	strcpy(g_d, s);
	return (g_d);
}

int	main(void)
{
	T("enough room returns total length", ft_strlcat(set("ab"), "cde", 12) == 5);
	T("enough room result", !memcmp(g_d, "abcde\0xxxxxx", 12));
	T("truncated returns the length it tried to make",
		ft_strlcat(set("ab"), "cde", 5) == 5);
	T("truncated result is terminated", !memcmp(g_d, "abcd\0xxxxxxx", 12));
	T("size 0 returns the length of src", ft_strlcat(set("ab"), "cde", 0) == 3);
	T("size 0 writes nothing", !memcmp(g_d, "ab\0xxxxxxxxx", 12));
	T("size smaller than dst returns size + src",
		ft_strlcat(set("ab"), "cde", 1) == 4);
	T("size smaller than dst writes nothing", !memcmp(g_d, "ab\0x", 4));
	T("size equal to dst length", ft_strlcat(set("ab"), "cde", 2) == 5);
	T("size equal to dst length writes nothing", !memcmp(g_d, "ab\0x", 4));
	T("room only for \\0", ft_strlcat(set("ab"), "cde", 3) == 5);
	T("room only for \\0 result", !memcmp(g_d, "ab\0x", 4));
	T("exact fit", ft_strlcat(set("ab"), "cde", 6) == 5
		&& !memcmp(g_d, "abcde\0xxxxxx", 12));
	T("empty dst", ft_strlcat(set(""), "cde", 12) == 3
		&& !memcmp(g_d, "cde\0xxxxxxxx", 12));
	T("empty src", ft_strlcat(set("ab"), "", 12) == 2
		&& !memcmp(g_d, "ab\0xxxxxxxxx", 12));
	return (t_end());
}
