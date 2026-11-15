#include "check.h"

/* searches n bytes as unsigned char, does not stop at \0 */
int	main(void)
{
	const char	*s = "hello\0world";
	char		b[3];

	T("found", ft_memchr(s, 'l', 11) == s + 2);
	T("not found", ft_memchr(s, 'z', 11) == NULL);
	T("n too small", ft_memchr(s, 'o', 4) == NULL);
	T("n just enough", ft_memchr(s, 'o', 5) == s + 4);
	T("n 0", ft_memchr(s, 'h', 0) == NULL);
	T("finds \\0", ft_memchr(s, '\0', 11) == s + 5);
	T("goes past \\0", ft_memchr(s, 'w', 11) == s + 6);
	T("c is converted to unsigned char (l + 256)",
		ft_memchr(s, 'l' + 256, 11) == s + 2);
	b[0] = 1;
	b[1] = (char)200;
	b[2] = 3;
	T("byte above 127", ft_memchr(b, 200, 3) == b + 1);
	T("byte above 127 given as negative", ft_memchr(b, -56, 3) == b + 1);
	return (t_end());
}
