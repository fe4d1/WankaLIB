#include "check.h"

static char	g_d[12];

/* fills the buffer with x then puts s: any extra write shows */
static char	*set(const char *s)
{
	memset(g_d, 'x', 12);
	strcpy(g_d, s);
	return (g_d);
}

/* returns the length it tried to make, never writes past size */
int	main(void)
{
	// size is the whole buffer, the return is strlen dst plus strlen src
	T("enough room returns total length", ft_strlcat(set("ab"), "cde", 12) == 5);
	// src is added after dst and terminated, nothing after it changes
	T("enough room result", !memcmp(g_d, "abcde\0xxxxxx", 12));
	// when it does not fit the return is still the full length
	// so the caller can see it was cut
	T("truncated returns the length it tried to make",
		ft_strlcat(set("ab"), "cde", 5) == 5);
	// it copies until size - 1 and puts the terminator
	T("truncated result is terminated", !memcmp(g_d, "abcd\0xxxxxxx", 12));
	// size 0 means dst has no room, the return is size plus strlen src
	T("size 0 returns the length of src", ft_strlcat(set("ab"), "cde", 0) == 3);
	// and nothing is written
	T("size 0 writes nothing", !memcmp(g_d, "ab\0xxxxxxxxx", 12));
	// size smaller than strlen dst returns size plus strlen src
	// and not strlen dst plus strlen src
	T("size smaller than dst returns size + src",
		ft_strlcat(set("ab"), "cde", 1) == 4);
	// nothing is written, not even a terminator
	T("size smaller than dst writes nothing", !memcmp(g_d, "ab\0x", 4));
	// size equal to strlen dst means no room either
	T("size equal to dst length", ft_strlcat(set("ab"), "cde", 2) == 5);
	// and nothing is written
	T("size equal to dst length writes nothing", !memcmp(g_d, "ab\0x", 4));
	// one byte of room is only for the terminator
	T("room only for \\0", ft_strlcat(set("ab"), "cde", 3) == 5);
	// so dst does not change
	T("room only for \\0 result", !memcmp(g_d, "ab\0x", 4));
	// exactly the room needed, catches an off by one at the end
	T("exact fit", ft_strlcat(set("ab"), "cde", 6) == 5
		&& !memcmp(g_d, "abcde\0xxxxxx", 12));
	// empty dst works like strlcpy
	T("empty dst", ft_strlcat(set(""), "cde", 12) == 3
		&& !memcmp(g_d, "cde\0xxxxxxxx", 12));
	// empty src adds nothing
	T("empty src", ft_strlcat(set("ab"), "", 12) == 2
		&& !memcmp(g_d, "ab\0xxxxxxxxx", 12));
	return (t_end());
}
