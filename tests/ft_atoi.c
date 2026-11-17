#include "check.h"
#include <stdlib.h>

/* compares with libc atoi and shows both numbers when they differ */
#define A(desc, s) do { \
	T(desc, ft_atoi(s) == atoi(s)); \
	if (ft_atoi(s) != atoi(s)) \
		t_note("input [%s] got %d expected %d", s, ft_atoi(s), atoi(s)); \
} while (0)

/* same result as libc atoi: spaces, one sign, stops at the first non digit */
int	main(void)
{
	// zero has no special case, the loop must still return 0
	A("0", "0");
	// the simplest positive number
	A("42", "42");
	// one minus sign makes it negative
	A("-42", "-42");
	// one plus sign is allowed and changes nothing
	A("+42", "+42");
	// spaces before the number are skipped
	A("spaces before", "   42");
	// isspace is 9 to 13 and 32 so tab newline vt ff cr are skipped too
	A("every isspace char before", "\t\n\v\f\r 42");
	// only one sign is allowed, a second sign means no number so 0
	A("--42", "--42");
	// same with two plus signs
	A("++42", "++42");
	// mixed signs also give 0
	A("+-42", "+-42");
	// and the other order too
	A("-+42", "-+42");
	// stops at the first char that is not a digit
	A("letters after", "42abc");
	// no digit at all gives 0
	A("only letters", "abc");
	// empty string gives 0 and must not read past the end
	A("empty", "");
	// a sign alone is not a number
	A("only -", "-");
	// same with plus
	A("only +", "+");
	// only spaces gives 0
	A("only a space", " ");
	// int max must fit without overflow
	A("int max", "2147483647");
	// int min is the classic overflow trap when you build it as positive
	A("int min", "-2147483648");
	// leading zeros are just digits
	A("leading zeros", "0000123");
	// minus zero is zero
	A("-000", "-000");
	// a space between sign and digits stops the parsing
	A("space after the sign", "  - 42");
	// a space inside the number stops it
	A("space inside", "4 2");
	// escape char 27 is not a space so nothing is skipped
	A("escape before", "\033" "42");
	// spaces after are just ignored
	A("space after", "42 ");
	// a sign in the middle stops the parsing
	A("sign in the middle", "1-2");
	// newlines around and a negative number
	A("newlines around", "\n-17\n");
	return (t_end());
}
