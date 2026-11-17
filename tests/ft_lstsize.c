#include "check.h"

/* counts nodes from the given one, 0 for an empty list */
int	main(void)
{
	t_list	*l;

	// NULL is a list of size 0
	T("empty list", ft_lstsize(NULL) == 0);
	l = t_node(strdup("a"));
	// catches a count that starts at 1 or misses the last node
	T("one node", ft_lstsize(l) == 1);
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	// a normal list
	T("three nodes", ft_lstsize(l) == 3);
	// counts from the given node to the end
	T("from the second node", ft_lstsize(l->next) == 2);
	t_lstfree(l);
	return (t_end());
}
