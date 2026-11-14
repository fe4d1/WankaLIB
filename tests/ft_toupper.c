#include "check.h"

static int	ref(int c)
{
	return (toupper(c));
}

int	main(void)
{
	T("same as libc for every c from -1 to 255", t_range(ft_toupper, ref));
	T("a", ft_toupper(0x61) == 0x41);
	T("z", ft_toupper(0x7a) == 0x5a);
	T("A stays", ft_toupper(0x41) == 0x41);
	T("5 stays", ft_toupper(0x35) == 0x35);
	T("{ stays", ft_toupper(123) == 123);
	T("-1 stays", ft_toupper(-1) == -1);
	return (t_end());
}
