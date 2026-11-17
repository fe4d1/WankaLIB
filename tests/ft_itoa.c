#include "check.h"
#include <stdlib.h>

/* digits, sign, INT_MIN, malloc failure */
int	main(void)
{
	// 0 has one digit, a loop while n > 0 returns an empty string
	TS("0", ft_itoa(0), "0");
	// one digit
	TS("1", ft_itoa(1), "1");
	// one digit and the sign, the length must count the minus
	TS("-1", ft_itoa(-1), "-1");
	// last number with one digit
	TS("9", ft_itoa(9), "9");
	// first number with two digits, catches a wrong digit count
	TS("10", ft_itoa(10), "10");
	// two digits and the sign
	TS("-10", ft_itoa(-10), "-10");
	// a normal number
	TS("42", ft_itoa(42), "42");
	// a normal negative number
	TS("-42", ft_itoa(-42), "-42");
	// zeros inside the number must not be lost
	TS("100000", ft_itoa(100000), "100000");
	// biggest int, ten digits
	TS("int max", ft_itoa(INT_MAX), "2147483647");
	// -INT_MIN does not fit in an int, use a long or handle it apart
	TS("int min", ft_itoa(INT_MIN), "-2147483648");
	// just above int min, -n still fits here
	TS("int min + 1", ft_itoa(INT_MIN + 1), "-2147483647");
	// when malloc fails itoa must return NULL
	MFAIL("malloc fails", ft_itoa(-123), free);
	return (t_end());
}
