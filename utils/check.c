#include "check.h"
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define GRN "\033[32m"
#define RED "\033[31m"
#define RST "\033[0m"

static const char	*g_desc = "start";
static int			g_n;
static int			g_ko;
static int			g_fail = -1;
static int			g_calls;
static size_t		g_max;
static int			g_pipe[2];

void	*__real_malloc(size_t n);

void	*__wrap_malloc(size_t n)
{
	if (g_fail >= 0 && g_calls++ == g_fail)
		return (NULL);
	if (n > g_max)
		g_max = n;
	return (__real_malloc(n));
}

void	fail_at(int n)
{
	g_fail = n;
	g_calls = 0;
}

int	fail_hit(void)
{
	return (g_calls > g_fail);
}

void	alloc_reset(void)
{
	g_max = 0;
}

size_t	alloc_max(void)
{
	return (g_max);
}

static void	crash(int sig)
{
	g_fail = -1;
	printf(RED "CRASH " RST);
	fprintf(stderr, "CRASH (%s) in test %d: %s\n", strsignal(sig), g_n + 1,
		g_desc);
	_exit(128 + sig);
}

__attribute__((constructor)) static void	t_init(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	signal(SIGSEGV, crash);
	signal(SIGBUS, crash);
	signal(SIGABRT, crash);
	signal(SIGFPE, crash);
}

void	t_set(const char *desc)
{
	g_desc = desc;
}

void	t_note(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	fprintf(stderr, "   ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

void	t_check(int ok, const char *expr, int line)
{
	g_n++;
	if (ok)
	{
		printf(GRN "OK " RST);
		return ;
	}
	g_ko++;
	printf(RED "KO " RST);
	fprintf(stderr, "KO test %d (line %d): %s\n   %s\n", g_n, line, g_desc,
		expr);
}

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

int	cap_open(void)
{
	if (pipe(g_pipe) < 0)
		return (-1);
	return (g_pipe[1]);
}

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

int	t_sign(int n)
{
	return ((n > 0) - (n < 0));
}

int	t_end(void)
{
	return (g_ko > 0);
}

t_list	*t_node(void *content)
{
	t_list	*n;

	n = __real_malloc(sizeof(t_list));
	n->content = content;
	n->next = NULL;
	return (n);
}

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
