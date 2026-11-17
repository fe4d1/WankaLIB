#include "check.h"

/* reference: space to ~ */
static int	ref(int c)
{
	return (c >= 32 && c <= 126);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	// the subject wants exactly 1 or 0 for every value
	// the trace shows the first c that is wrong
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isprint, ref));
	// space is the first printable char
	T("space", ft_isprint(32) == 1);
	// tilde is the last printable char
	T("~", ft_isprint(126) == 1);
	// 31 is a control char just before space
	T("31", ft_isprint(31) == 0);
	// 127 DEL is ascii but not printable
	T("127 DEL", ft_isprint(127) == 0);
	// newline is a control char
	T("newline", ft_isprint(10) == 0);
	return (t_end());
}
