#include "check.h"

static int	g_calls;

/* adds the index to the char and counts its calls */
static void	add_index(unsigned int i, char *c)
{
	*c += i;
	g_calls++;
}

/* uppercases only the char at index 0 */
static void	upper_first(unsigned int i, char *c)
{
	if (i == 0)
		*c = toupper(*c);
}

/* f gets the index and the address of each char, changed in place */
int	main(void)
{
	char	a[] = "aaaa";
	char	b[] = "hello";
	char	e[] = "";

	ft_striteri(a, add_index);
	T("index is passed and string is modified in place", !strcmp(a, "abcd"));
	T("f called once per char", g_calls == 4);
	ft_striteri(b, upper_first);
	T("f gets the address of each char", !strcmp(b, "Hello"));
	g_calls = 0;
	ft_striteri(e, add_index);
	T("empty string never calls f", g_calls == 0);
	return (t_end());
}
