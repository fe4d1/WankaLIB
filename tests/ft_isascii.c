#include "check.h"

/* reference: 0 to 127 */
static int	ref(int c)
{
	return (c >= 0 && c <= 127);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isascii, ref));
	T("0", ft_isascii(0) == 1);
	T("127", ft_isascii(127) == 1);
	T("128", ft_isascii(128) == 0);
	T("-1", ft_isascii(-1) == 0);
	return (t_end());
}
