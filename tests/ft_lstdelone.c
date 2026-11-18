#include "list.h"
#include <stdlib.h>

static int	g_del;

/* counts its calls and frees the content */
static void	del(void *p)
{
	g_del++;
	free(p);
}

/* frees one node only, never the next one */
int	main(void)
{
	t_list	*a;
	t_list	*b;

	a = t_node(strdup("a"));
	b = t_node(strdup("b"));
	a->next = b;
	ft_lstdelone(a, del);
	// del frees the content once, the node itself is freed with free
	T("del called once", g_del == 1);
	// next must not be freed, valgrind shows an invalid read if it was
	T("next node is not freed", !strcmp(b->content, "b") && b->next == NULL);
	ft_lstdelone(b, del);
	// a node with no next
	T("single node", g_del == 2);
	return (t_end());
}
