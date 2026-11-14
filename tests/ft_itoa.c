#include "check.h"
#include <stdlib.h>

int	main(void)
{
	TS("0", ft_itoa(0), "0");
	TS("1", ft_itoa(1), "1");
	TS("-1", ft_itoa(-1), "-1");
	TS("9", ft_itoa(9), "9");
	TS("10", ft_itoa(10), "10");
	TS("-10", ft_itoa(-10), "-10");
	TS("42", ft_itoa(42), "42");
	TS("-42", ft_itoa(-42), "-42");
	TS("100000", ft_itoa(100000), "100000");
	TS("int max", ft_itoa(INT_MAX), "2147483647");
	TS("int min", ft_itoa(INT_MIN), "-2147483648");
	TS("int min + 1", ft_itoa(INT_MIN + 1), "-2147483647");
	MFAIL("malloc fails", ft_itoa(-123), free);
	return (t_end());
}
