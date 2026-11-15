#include "check.h"
#include <stdlib.h>

static int	g_del;

/* counts its calls and frees the content */
static void	del(void *p)
{
	g_del++;
	free(p);
}

/* del on every node from the given one, pointer set to NULL */
int	main(void)
{
	t_list	*l;
	t_list	*mid;

	l = t_node(strdup("a"));
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	ft_lstclear(&l, del);
	T("del called for every node", g_del == 3);
	T("list pointer set to NULL", l == NULL);
	ft_lstclear(&l, del);
	T("empty list", l == NULL && g_del == 3);
	l = t_node(strdup("a"));
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	mid = l->next;
	g_del = 0;
	ft_lstclear(&mid, del);
	T("from the middle frees only the rest", g_del == 2 && mid == NULL);
	l->next = NULL;
	ft_lstclear(&l, del);
	T("one node", g_del == 3 && l == NULL);
	return (t_end());
}
