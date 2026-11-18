#ifndef CHECK_H
# define CHECK_H

# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
# include <stdint.h>

/*
** every test is numbered on screen (1)OK 2)OK 3)KO) and in the trace
** (KO test 3 (line 20)), write a // comment above a test to explain why it
** exists: the runner copies it into the trace when that test fails
**
** T(desc, condition)            one test
** TS(desc, got, expected)       string result, frees got
** TT(desc, got, "a", "b")       split result, frees got
** OUT(desc, call, expected)     output written on fd (use the variable fd)
** MFAIL(desc, call, cleanup)    makes every malloc of call fail in turn
*/

# define T(desc, cond) (t_set(desc, __LINE__), t_check((cond), #cond, __LINE__))
# define TS(desc, got, exp) (t_set(desc, __LINE__), t_str((got), (exp), __LINE__))
# define TT(desc, got, ...) (t_set(desc, __LINE__), \
	t_tab((got), (const char *[]){__VA_ARGS__, NULL}, __LINE__))
# define OUT(desc, call, exp) OUTN(desc, call, exp, strlen(exp))
# define OUTN(desc, call, exp, len) do { \
	int fd = cap_open(); \
	t_set(desc, __LINE__); \
	call; \
	t_out((exp), (len), __LINE__); \
} while (0)
# define MFAIL(desc, call, cleanup) do { \
	int i_ = 0; \
	while (i_ < 100) { \
		t_set(desc, __LINE__); \
		fail_at(i_); \
		void *r_ = (void *)(call); \
		int hit_ = fail_hit(); \
		fail_at(-1); \
		if (!hit_) { cleanup(r_); break ; } \
		if (r_) t_note("malloc call number %d failed", i_ + 1); \
		t_check(r_ == NULL, "returns NULL when a malloc fails", __LINE__); \
		if (r_) cleanup(r_); \
		i_++; \
	} \
} while (0)

void	t_set(const char *desc, int line);
void	t_check(int ok, const char *expr, int line);
void	t_str(char *got, const char *exp, int line);
void	t_tab(char **got, const char **exp, int line);
void	t_out(const char *exp, size_t len, int line);
void	t_note(const char *fmt, ...);
int		t_range(int (*ft)(int), int (*ref)(int));
int		t_sign(int n);
int		t_end(void);

void	fail_at(int n);
int		fail_hit(void);
void	alloc_reset(void);
size_t	alloc_max(void);
int		cap_open(void);

void	t_tabfree(void *tab);

#endif
