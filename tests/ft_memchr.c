#include "check.h"

/* searches n bytes as unsigned char, does not stop at \0 */
int	main(void)
{
	const char	*s = "hello\0world";
	char		b[3];

	// returns a pointer to the first match
	T("found", ft_memchr(s, 'l', 11) == s + 2);
	// no match in n bytes gives NULL
	T("not found", ft_memchr(s, 'z', 11) == NULL);
	// only the first n bytes are searched, o is at index 4
	T("n too small", ft_memchr(s, 'o', 4) == NULL);
	// the last byte inside n counts, catches an off by one
	T("n just enough", ft_memchr(s, 'o', 5) == s + 4);
	// n 0 searches nothing
	T("n 0", ft_memchr(s, 'h', 0) == NULL);
	// a zero byte is a normal byte for mem functions
	T("finds \\0", ft_memchr(s, '\0', 11) == s + 5);
	// unlike strchr it keeps going after a zero byte
	T("goes past \\0", ft_memchr(s, 'w', 11) == s + 6);
	// c is an int but it is compared as unsigned char, 364 becomes 108
	T("c is converted to unsigned char (l + 256)",
		ft_memchr(s, 'l' + 256, 11) == s + 2);
	b[0] = 1;
	b[1] = (char)200;
	b[2] = 3;
	// a byte above 127 is negative as char, compare as unsigned char
	T("byte above 127", ft_memchr(b, 200, 3) == b + 1);
	// -56 as unsigned char is 200 too
	T("byte above 127 given as negative", ft_memchr(b, -56, 3) == b + 1);
	return (t_end());
}
