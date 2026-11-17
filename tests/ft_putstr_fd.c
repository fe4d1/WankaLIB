#include "check.h"

/* writes the string as it is, nothing added */
int	main(void)
{
	// the string on the given fd and not on stdout
	OUT("hello", ft_putstr_fd("hello", fd), "hello");
	// an empty string writes nothing
	OUT("empty writes nothing", ft_putstr_fd("", fd), "");
	// newlines inside are written as they are
	OUT("with newline", ft_putstr_fd("a\nb\n", fd), "a\nb\n");
	// putstr adds nothing, that is putendl
	OUT("no newline added", ft_putstr_fd("abc", fd), "abc");
	// the whole string, no fixed buffer that cuts it
	OUT("long string", ft_putstr_fd("0123456789012345678901234567890123456789",
			fd), "0123456789012345678901234567890123456789");
	return (t_end());
}
