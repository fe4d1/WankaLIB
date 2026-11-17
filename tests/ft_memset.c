#include "check.h"

/* fills len bytes with c as unsigned char, returns the pointer */
int	main(void)
{
	char	a[12];
	int		n;

	memset(a, 'x', 12);
	// memset returns the original pointer, not the end
	T("returns the pointer", ft_memset(a + 1, 'A', 10) == a + 1);
	// the x around catch a byte written too far or too early
	T("fills len bytes and no more", !memcmp(a, "xAAAAAAAAAAx", 12));
	ft_memset(a + 1, 300, 10);
	// c is an int but only one byte is written, 300 as unsigned char is 44
	T("c is converted to unsigned char (300 is 44)",
		a[1] == 44 && a[10] == 44 && a[0] == 'x' && a[11] == 'x');
	memset(a, 'x', 12);
	ft_memset(a, 'B', 0);
	// len 0 must not write
	T("len 0 writes nothing", a[0] == 'x');
	ft_memset(a, 0, 12);
	// c 0 is a normal value
	T("c = 0", !memcmp(a, "\0\0\0\0\0\0\0\0\0\0\0\0", 12));
	n = 123456;
	ft_memset(&n, 0, sizeof(n));
	// void pointer means any type
	T("works on an int", n == 0);
	ft_memset(&n, 1, sizeof(n));
	// every byte is 1 so the int is 0x01010101 and not 1
	// casting to int pointer and writing ints fails here
	T("writes bytes not ints", n == 0x01010101);
	return (t_end());
}
