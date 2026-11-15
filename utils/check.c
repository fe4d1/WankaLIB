#include "check.h"
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define PASS "\033[1;97m"
#define FAIL "\033[1;97;41m"
#define RST "\033[0m"

static const char	*g_desc = "start";
static int			g_n;
static int			g_ko;
static int			g_fail = -1;
static int			g_calls;
static size_t		g_max;
static int			g_pipe[2];

void	*__real_malloc(size_t n);

/* replaces malloc inside the libft: fails on the chosen call */
void	*__wrap_malloc(size_t n)
{
	if (g_fail >= 0 && g_calls++ == g_fail)
		return (NULL);
	if (n > g_max)
		g_max = n;
	return (__real_malloc(n));
}

/* the nth malloc from now will fail (-1: none) */
void	fail_at(int n)
{
	g_fail = n;
	g_calls = 0;
}

/* 1 if the malloc chosen to fail was reached */
int	fail_hit(void)
{
	return (g_calls > g_fail);
}

/* forgets the biggest size seen */
void	alloc_reset(void)
{
	g_max = 0;
}

/* biggest size asked to malloc since the reset */
size_t	alloc_max(void)
{
	return (g_max);
}

/* signal handler: says which test crashed and exits */
static void	crash(int sig)
{
	g_fail = -1;
	printf(FAIL "CRASH" RST " ");
	fprintf(stderr, "CRASH (%s) in test %d: %s\n", strsignal(sig), g_n + 1,
		g_desc);
	_exit(128 + sig);
}

/* runs before main: unbuffered output, catches the crash signals */
__attribute__((constructor)) static void	t_init(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	signal(SIGSEGV, crash);
	signal(SIGBUS, crash);
	signal(SIGABRT, crash);
	signal(SIGFPE, crash);
}

/* name of the next test, used in the reports */
void	t_set(const char *desc)
{
	g_desc = desc;
}

/* extra detail line in the trace */
void	t_note(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	fprintf(stderr, "   ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

/* one test: prints OK or KO, a KO goes to the trace with its line */
void	t_check(int ok, const char *expr, int line)
{
	g_n++;
	if (ok)
	{
		printf(PASS "OK " RST);
		return ;
	}
	g_ko++;
	printf(FAIL "KO" RST " ");
	fprintf(stderr, "KO test %d (line %d): %s\n   %s\n", g_n, line, g_desc,
		expr);
}

/* compares a returned string with the expected one, then frees it */
void	t_str(char *got, const char *exp, int line)
{
	int	ok;

	ok = (got && exp && !strcmp(got, exp)) || (!got && !exp);
	t_check(ok, "string result", line);
	if (!ok)
		t_note("got      [%s]\n   expected [%s]", got ? got : "NULL",
			exp ? exp : "NULL");
	free(got);
}

/* compares a split result word by word, then frees it */
void	t_tab(char **got, const char **exp, int line)
{
	int	i;
	int	ok;

	i = 0;
	ok = (got != NULL);
	while (ok && (got[i] || exp[i]))
	{
		if (!got[i] || !exp[i] || strcmp(got[i], exp[i]))
		{
			ok = 0;
			t_note("word %d got [%s] expected [%s]", i,
				got[i] ? got[i] : "NULL", exp[i] ? exp[i] : "NULL");
		}
		else
			i++;
	}
	if (!got)
		t_note("got NULL");
	t_check(ok, "array result", line);
	t_tabfree(got);
}

/* frees a NULL terminated array of strings */
void	t_tabfree(void *tab)
{
	char	**t;
	int		i;

	t = tab;
	i = 0;
	while (t && t[i])
		free(t[i++]);
	free(t);
}

/* opens a pipe and returns the fd the function must write on */
int	cap_open(void)
{
	if (pipe(g_pipe) < 0)
		return (-1);
	return (g_pipe[1]);
}

/* reads what was written on the pipe and compares it */
void	t_out(const char *exp, size_t len, int line)
{
	char	buf[4096];
	ssize_t	n;
	int		ok;

	close(g_pipe[1]);
	n = read(g_pipe[0], buf, sizeof(buf) - 1);
	close(g_pipe[0]);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	ok = ((size_t)n == len && !memcmp(buf, exp, len));
	t_check(ok, "output on fd", line);
	if (!ok)
		t_note("got      [%s] (%zd bytes)\n   expected [%s] (%zu bytes)",
			buf, n, exp, len);
}

/* compares ft and ref for every c from -1 to 255 */
int	t_range(int (*ft)(int), int (*ref)(int))
{
	int	c;

	c = -1;
	while (c <= 255)
	{
		if (ft(c) != ref(c))
		{
			t_note("c = %d got %d expected %d", c, ft(c), ref(c));
			return (0);
		}
		c++;
	}
	return (1);
}

/* -1, 0 or 1 */
int	t_sign(int n)
{
	return ((n > 0) - (n < 0));
}

/* exit status: 1 if a test failed */
int	t_end(void)
{
	return (g_ko > 0);
}

/* makes a node with the real malloc, so it never fails */
t_list	*t_node(void *content)
{
	t_list	*n;

	n = __real_malloc(sizeof(t_list));
	n->content = content;
	n->next = NULL;
	return (n);
}

/* frees a whole list and its contents */
void	t_lstfree(void *lst)
{
	t_list	*l;
	t_list	*next;

	l = lst;
	while (l)
	{
		next = l->next;
		free(l->content);
		free(l);
		l = next;
	}
}
