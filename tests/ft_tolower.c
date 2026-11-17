#include "check.h"

/* reference: libc */
static int	ref(int c)
{
	return (tolower(c));
}

/* only A-Z change, same as libc on -1..255 */
int	main(void)
{
	// every value from EOF to 255 must give the same as libc
	// the trace shows the first c that is wrong
	T("same as libc for every c from -1 to 255", t_range(ft_tolower, ref));
	// the first uppercase letter
	T("A", ft_tolower(0x41) == 0x61);
	// the last uppercase letter
	T("Z", ft_tolower(0x5a) == 0x7a);
	// a lowercase letter does not change
	T("a stays", ft_tolower(0x61) == 0x61);
	// the char just after Z does not change
	T("[ stays", ft_tolower(91) == 91);
	// EOF comes back as it is
	T("-1 stays", ft_tolower(-1) == -1);
	return (t_end());
}
