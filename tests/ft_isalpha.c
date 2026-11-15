#include "check.h"

/* reference: libc result reduced to 1 or 0 */
static int	ref(int c)
{
	return (isalpha(c) != 0);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isalpha, ref));
	T("a", ft_isalpha(0x61) == 1);
	T("Z", ft_isalpha(0x5a) == 1);
	T("@ is just before A", ft_isalpha(64) == 0);
	T("[ is just after Z", ft_isalpha(91) == 0);
	T("5", ft_isalpha(0x35) == 0);
	T("300", ft_isalpha(300) == 0);
	return (t_end());
}
