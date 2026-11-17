#include "check.h"

/* reference: libc result reduced to 1 or 0 */
static int	ref(int c)
{
	return (isalnum(c) != 0);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	// libc returns any non zero value but the subject wants exactly 1 or 0
	// the trace shows the first c that is wrong
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isalnum, ref));
	// a letter is alnum
	T("a", ft_isalnum(0x61) == 1);
	// a digit is alnum
	T("7", ft_isalnum(0x37) == 1);
	// space is neither
	T("space", ft_isalnum(32) == 0);
	// underscore looks like part of a word but it is not alnum
	T("_", ft_isalnum(95) == 0);
	return (t_end());
}
