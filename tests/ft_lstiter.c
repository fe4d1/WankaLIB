#include "list.h"

static char	g_seen[8];
static int	g_n;

/* records each content, to check the order */
static void	see(void *p)
{
	if (g_n < 7)
		g_seen[g_n++] = *(char *)p;
}

/* uppercases the content in place */
static void	upper(void *p)
{
	*(char *)p = toupper(*(char *)p);
}

/* f runs once per node, in order, on the real content */
int	main(void)
{
	t_list	*l;

	l = t_node(strdup("a"));
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	ft_lstiter(l, see);
	// f gets the content and not the node, once per node from head to tail
	T("f called on every content in order", !strcmp(g_seen, "abc"));
	ft_lstiter(l, upper);
	// f works on the real content and not on a copy
	T("f can modify the content", !strcmp(l->content, "A")
		&& !strcmp(l->next->next->content, "C"));
	g_n = 0;
	ft_lstiter(NULL, see);
	// an empty list must not call f or crash
	T("empty list never calls f", g_n == 0);
	t_lstfree(l);
	return (t_end());
}
