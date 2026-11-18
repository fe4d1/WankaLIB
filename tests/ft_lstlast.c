#include "list.h"

/* returns the last node, NULL for an empty list */
int	main(void)
{
	t_list	*l;

	// an empty list has no last node, reading lst->next here crashes
	T("empty list returns NULL", ft_lstlast(NULL) == NULL);
	l = t_node(strdup("a"));
	// one node is its own last
	T("one node", ft_lstlast(l) == l);
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	// returns the node and not its content, and not NULL after the end
	T("three nodes", ft_lstlast(l) == l->next->next);
	// starting at the last node
	T("from the last node", ft_lstlast(l->next->next) == l->next->next);
	t_lstfree(l);
	return (t_end());
}
