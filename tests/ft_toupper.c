#include "check.h"

/* reference: libc */
static int	ref(int c)
{
	return (toupper(c));
}

/* only a-z change, same as libc on -1..255 */
int	main(void)
{
	// every value from EOF to 255 must give the same as libc
	// the trace shows the first c that is wrong
	T("same as libc for every c from -1 to 255", t_range(ft_toupper, ref));
	// the first lowercase letter
	T("a", ft_toupper(0x61) == 0x41);
	// the last lowercase letter
	T("z", ft_toupper(0x7a) == 0x5a);
	// an uppercase letter does not change
	T("A stays", ft_toupper(0x41) == 0x41);
	// a digit does not change
	T("5 stays", ft_toupper(0x35) == 0x35);
	// the char just after z does not change
	T("{ stays", ft_toupper(123) == 123);
	// EOF comes back as it is
	T("-1 stays", ft_toupper(-1) == -1);
	return (t_end());
}
