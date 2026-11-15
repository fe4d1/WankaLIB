#include "check.h"

/* reference: '0' to '9' */
static int	ref(int c)
{
	return (c >= 48 && c <= 57);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isdigit, ref));
	T("0", ft_isdigit(48) == 1);
	T("9", ft_isdigit(57) == 1);
	T("/ is just before 0", ft_isdigit(47) == 0);
	T(": is just after 9", ft_isdigit(58) == 0);
	T("the number 5 is not the char 5", ft_isdigit(5) == 0);
	return (t_end());
}
