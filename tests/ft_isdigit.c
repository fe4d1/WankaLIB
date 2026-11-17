#include "check.h"

/* reference: '0' to '9' */
static int	ref(int c)
{
	return (c >= 48 && c <= 57);
}

/* returns exactly 1 or 0: whole range -1..255 plus the borders */
int	main(void)
{
	// the subject wants exactly 1 or 0 for every value
	// the trace shows the first c that is wrong
	T("exactly 1 or 0 for every c from -1 to 255", t_range(ft_isdigit, ref));
	// the char 0 is 48
	T("0", ft_isdigit(48) == 1);
	// the char 9 is 57
	T("9", ft_isdigit(57) == 1);
	// borders catch a < that should be <= and the other way round
	T("/ is just before 0", ft_isdigit(47) == 0);
	// same border after 9
	T(": is just after 9", ft_isdigit(58) == 0);
	// classic mistake: checking 0 to 9 instead of 48 to 57
	T("the number 5 is not the char 5", ft_isdigit(5) == 0);
	return (t_end());
}
