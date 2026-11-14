#include "check.h"

int	main(void)
{
	OUT("hello", ft_putendl_fd("hello", fd), "hello\n");
	OUT("empty writes only the newline", ft_putendl_fd("", fd), "\n");
	OUT("string that already ends with newline", ft_putendl_fd("a\n", fd),
		"a\n\n");
	return (t_end());
}
