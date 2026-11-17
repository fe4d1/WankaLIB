#include "check.h"

/* node becomes the head and points to the old head */
int	main(void)
{
	t_list	*l;
	t_list	*a;
	t_list	*b;

	l = NULL;
	a = t_node(strdup("a"));
	b = t_node(strdup("b"));
	ft_lstadd_front(&l, a);
	// on an empty list the new node is the whole list
	T("empty list", l == a && a->next == NULL);
	ft_lstadd_front(&l, b);
	// the head pointer of the caller must change
	T("new node becomes the head", l == b);
	// the new node links to the old head, nothing is lost
	T("old head is second", b->next == a && a->next == NULL);
	t_lstfree(l);
	return (t_end());
}
