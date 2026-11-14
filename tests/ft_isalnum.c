#include "check.h"

static int	ref(int c)
{
	return (isalnum(c) != 0);
}

int	main(void)
{
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isalnum, ref));
	T("a", ft_isalnum(0x61) == 1);
	T("7", ft_isalnum(0x37) == 1);
	T("space", ft_isalnum(32) == 0);
	T("_", ft_isalnum(95) == 0);
	return (t_end());
}
