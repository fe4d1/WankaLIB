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
	// f gets 0 1 2 3 as index, aaaa becomes abcd in the same string
	T("index is passed and string is modified in place", !strcmp(a, "abcd"));
	// once per char, not for the terminator
	T("f called once per char", g_calls == 4);
	ft_striteri(b, upper_first);
	// f gets the address of the real char, so the change stays
	T("f gets the address of each char", !strcmp(b, "Hello"));
	g_calls = 0;
	ft_striteri(e, add_index);
	// an empty string has no char so f is never called
	T("empty string never calls f", g_calls == 0);
	return (t_end());
}
