#include "check.h"

/* writes exactly one byte on fd, even \0 or above 127 */
int	main(void)
{
	// one byte on the given fd and not on stdout
	OUT("a", ft_putchar_fd('a', fd), "a");
	// newline is a normal byte
	OUT("newline", ft_putchar_fd('\n', fd), "\n");
	// space is a normal byte
	OUT("space", ft_putchar_fd(' ', fd), " ");
	// a zero byte is still written, write with size 1 and not strlen
	OUTN("\\0 is one byte", ft_putchar_fd('\0', fd), "\0", 1);
	// a negative char is written as the same byte
	OUTN("char above 127", ft_putchar_fd((char)200, fd), "\310", 1);
	return (t_end());
}
