#include "check.h"

/* returns strlen(src), copies at most size - 1, always ends with \0 */
int	main(void)
{
	char	d[10];

	memset(d, 'x', 10);
	// the return is always strlen src
	T("returns the length of src", ft_strlcpy(d, "hello", 10) == 5);
	// copies and terminates, nothing after the terminator changes
	T("copies and terminates", !memcmp(d, "hello\0xxxx", 10));
	memset(d, 'x', 10);
	// even when it is cut the return is strlen src
	T("truncated still returns the length of src",
		ft_strlcpy(d, "hello", 3) == 5);
	// copies size - 1 chars and the terminator
	T("truncated is terminated", !memcmp(d, "he\0xxxxxxx", 10));
	memset(d, 'x', 10);
	// size 0 still returns strlen src
	T("size 0 returns the length of src", ft_strlcpy(d, "hello", 0) == 5);
	// with size 0 there is no room, not even for the terminator
	T("size 0 writes nothing", d[0] == 'x');
	ft_strlcpy(d, "hello", 1);
	// size 1 is only room for the terminator
	T("size 1 writes only \\0", d[0] == '\0' && d[1] == 'x');
	memset(d, 'x', 10);
	ft_strlcpy(d, "hello", 6);
	// exactly the room needed, catches an off by one at the end
	T("exact fit", !memcmp(d, "hello\0xxxx", 10));
	memset(d, 'x', 10);
	// empty src
	T("empty src returns 0", ft_strlcpy(d, "", 10) == 0);
	// empty src still writes the terminator
	T("empty src writes only \\0", d[0] == '\0' && d[1] == 'x');
	return (t_end());
}
