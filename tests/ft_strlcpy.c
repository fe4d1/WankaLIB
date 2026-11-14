#include "check.h"

int	main(void)
{
	char	d[10];

	memset(d, 'x', 10);
	T("returns the length of src", ft_strlcpy(d, "hello", 10) == 5);
	T("copies and terminates", !memcmp(d, "hello\0xxxx", 10));
	memset(d, 'x', 10);
	T("truncated still returns the length of src",
		ft_strlcpy(d, "hello", 3) == 5);
	T("truncated is terminated", !memcmp(d, "he\0xxxxxxx", 10));
	memset(d, 'x', 10);
	T("size 0 returns the length of src", ft_strlcpy(d, "hello", 0) == 5);
	T("size 0 writes nothing", d[0] == 'x');
	ft_strlcpy(d, "hello", 1);
	T("size 1 writes only \\0", d[0] == '\0' && d[1] == 'x');
	memset(d, 'x', 10);
	ft_strlcpy(d, "hello", 6);
	T("exact fit", !memcmp(d, "hello\0xxxx", 10));
	memset(d, 'x', 10);
	T("empty src returns 0", ft_strlcpy(d, "", 10) == 0);
	T("empty src writes only \\0", d[0] == '\0' && d[1] == 'x');
	return (t_end());
}
