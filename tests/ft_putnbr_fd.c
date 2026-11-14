#include "check.h"

int	main(void)
{
	OUT("0", ft_putnbr_fd(0, fd), "0");
	OUT("1", ft_putnbr_fd(1, fd), "1");
	OUT("-1", ft_putnbr_fd(-1, fd), "-1");
	OUT("9", ft_putnbr_fd(9, fd), "9");
	OUT("10", ft_putnbr_fd(10, fd), "10");
	OUT("-10", ft_putnbr_fd(-10, fd), "-10");
	OUT("42", ft_putnbr_fd(42, fd), "42");
	OUT("100000", ft_putnbr_fd(100000, fd), "100000");
	OUT("int max", ft_putnbr_fd(INT_MAX, fd), "2147483647");
	OUT("int min", ft_putnbr_fd(INT_MIN, fd), "-2147483648");
	return (t_end());
}
