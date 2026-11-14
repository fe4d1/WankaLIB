#include "check.h"
#include <stdlib.h>

static int	g_del;

static void	del(void *p)
{
	g_del++;
	free(p);
}

int	main(void)
{
	t_list	*a;
	t_list	*b;

	a = t_node(strdup("a"));
	b = t_node(strdup("b"));
	a->next = b;
	ft_lstdelone(a, del);
	T("del called once", g_del == 1);
	T("next node is not freed", !strcmp(b->content, "b") && b->next == NULL);
	ft_lstdelone(b, del);
	T("single node", g_del == 2);
	return (t_end());
}
