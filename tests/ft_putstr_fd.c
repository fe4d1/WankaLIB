#include "check.h"

int	main(void)
{
	OUT("hello", ft_putstr_fd("hello", fd), "hello");
	OUT("empty writes nothing", ft_putstr_fd("", fd), "");
	OUT("with newline", ft_putstr_fd("a\nb\n", fd), "a\nb\n");
	OUT("no newline added", ft_putstr_fd("abc", fd), "abc");
	OUT("long string", ft_putstr_fd("0123456789012345678901234567890123456789",
			fd), "0123456789012345678901234567890123456789");
	return (t_end());
}
