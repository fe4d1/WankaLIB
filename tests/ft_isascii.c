#include "check.h"

/* reference: 0 to 127 */
static int	ref(int c)
{
	return (c >= 0 && c <= 127);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	// the subject wants exactly 1 or 0 for every value
	// the trace shows the first c that is wrong
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isascii, ref));
	// 0 is the first ascii value, a > 0 instead of >= 0 fails here
	T("0", ft_isascii(0) == 1);
	// 127 DEL is the last ascii value
	T("127", ft_isascii(127) == 1);
	// 128 is just after the end
	T("128", ft_isascii(128) == 0);
	// EOF is -1 and it is not ascii
	T("-1", ft_isascii(-1) == 0);
	return (t_end());
}
