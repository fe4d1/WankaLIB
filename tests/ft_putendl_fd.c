#include "check.h"

/* writes the string plus one newline */
int	main(void)
{
	// the string and then one newline
	OUT("hello", ft_putendl_fd("hello", fd), "hello\n");
	// an empty string still gets its newline
	OUT("empty writes only the newline", ft_putendl_fd("", fd), "\n");
	// the newline is always added, even if there is one already
	OUT("string that already ends with newline", ft_putendl_fd("a\n", fd),
		"a\n\n");
	return (t_end());
}
