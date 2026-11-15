#include "check.h"
#include <stdlib.h>

/* same result as libc atoi: spaces, one sign, stops at the first non digit */
int	main(void)
{
	const char	*v[] = {"0", "42", "-42", "+42", "   42", "\t\n\v\f\r 42",
		"--42", "++42", "+-42", "-+42", "42abc", "abc", "", "-", "+", " ",
		"2147483647", "-2147483648", "0000123", "-000", "  - 42", "4 2",
		"\033" "42", "42 ", "1-2", "\n-17\n", NULL};
	int			i;

	i = 0;
	while (v[i])
	{
		T(v[i], ft_atoi(v[i]) == atoi(v[i]));
		if (ft_atoi(v[i]) != atoi(v[i]))
			t_note("got %d expected %d", ft_atoi(v[i]), atoi(v[i]));
		i++;
	}
	return (t_end());
}
