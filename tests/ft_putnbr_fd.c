#include "check.h"

/* writes digits, sign and INT_MIN */
int	main(void)
{
	// 0 has one digit, a loop while n > 0 writes nothing
	OUT("0", ft_putnbr_fd(0, fd), "0");
	// one digit
	OUT("1", ft_putnbr_fd(1, fd), "1");
	// sign and one digit
	OUT("-1", ft_putnbr_fd(-1, fd), "-1");
	// last number with one digit
	OUT("9", ft_putnbr_fd(9, fd), "9");
	// first number with two digits, the digits must come in order
	OUT("10", ft_putnbr_fd(10, fd), "10");
	// two digits and the sign
	OUT("-10", ft_putnbr_fd(-10, fd), "-10");
	// a normal number
	OUT("42", ft_putnbr_fd(42, fd), "42");
	// zeros inside the number must be written
	OUT("100000", ft_putnbr_fd(100000, fd), "100000");
	// biggest int
	OUT("int max", ft_putnbr_fd(INT_MAX, fd), "2147483647");
	// -INT_MIN does not fit in an int, use a long or handle it apart
	OUT("int min", ft_putnbr_fd(INT_MIN, fd), "-2147483648");
	return (t_end());
}
