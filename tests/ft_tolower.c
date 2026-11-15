#include "check.h"

/* reference: libc */
static int	ref(int c)
{
	return (tolower(c));
}

/* only A-Z change, same as libc on -1..255 */
int	main(void)
{
	T("same as libc for every c from -1 to 255", t_range(ft_tolower, ref));
	T("A", ft_tolower(0x41) == 0x61);
	T("Z", ft_tolower(0x5a) == 0x7a);
	T("a stays", ft_tolower(0x61) == 0x61);
	T("[ stays", ft_tolower(91) == 91);
	T("-1 stays", ft_tolower(-1) == -1);
	return (t_end());
}
