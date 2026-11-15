#include "check.h"

/* counts nodes from the given one, 0 for an empty list */
int	main(void)
{
	t_list	*l;

	T("empty list", ft_lstsize(NULL) == 0);
	l = t_node(strdup("a"));
	T("one node", ft_lstsize(l) == 1);
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	T("three nodes", ft_lstsize(l) == 3);
	T("from the second node", ft_lstsize(l->next) == 2);
	t_lstfree(l);
	return (t_end());
}
