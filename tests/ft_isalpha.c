#include "check.h"

/* reference: libc result reduced to 1 or 0 */
static int	ref(int c)
{
	return (isalpha(c) != 0);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	// libc returns any non zero value but the subject wants exactly 1 or 0
	// the trace shows the first c that is wrong
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isalpha, ref));
	// lowercase letter
	T("a", ft_isalpha(0x61) == 1);
	// uppercase letter, the last one
	T("Z", ft_isalpha(0x5a) == 1);
	// borders catch a < that should be <= and the other way round
	T("@ is just before A", ft_isalpha(64) == 0);
	// same border after Z
	T("[ is just after Z", ft_isalpha(91) == 0);
	// a digit is not a letter
	T("5", ft_isalpha(0x35) == 0);
	// values above 255 are not letters even if 300 % 256 would be
	T("300", ft_isalpha(300) == 0);
	return (t_end());
}
