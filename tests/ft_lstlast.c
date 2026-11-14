#include "check.h"

int	main(void)
{
	t_list	*l;

	T("empty list returns NULL", ft_lstlast(NULL) == NULL);
	l = t_node(strdup("a"));
	T("one node", ft_lstlast(l) == l);
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	T("three nodes", ft_lstlast(l) == l->next->next);
	T("from the last node", ft_lstlast(l->next->next) == l->next->next);
	t_lstfree(l);
	return (t_end());
}
