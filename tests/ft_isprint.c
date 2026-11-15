#include "check.h"

/* reference: space to ~ */
static int	ref(int c)
{
	return (c >= 32 && c <= 126);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isprint, ref));
	T("space", ft_isprint(32) == 1);
	T("~", ft_isprint(126) == 1);
	T("31", ft_isprint(31) == 0);
	T("127 DEL", ft_isprint(127) == 0);
	T("newline", ft_isprint(10) == 0);
	return (t_end());
}
