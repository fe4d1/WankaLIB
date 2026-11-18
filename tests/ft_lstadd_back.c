#include "list.h"

/* node goes last, head changes only if the list was empty */
int	main(void)
{
	t_list	*l;
	t_list	*a;
	t_list	*b;
	t_list	*c;

	l = NULL;
	a = t_node(strdup("a"));
	b = t_node(strdup("b"));
	c = t_node(strdup("c"));
	ft_lstadd_back(&l, a);
	// on an empty list there is no last node, the new one becomes the head
	// that is why the function gets a pointer to the head
	T("empty list", l == a && a->next == NULL);
	ft_lstadd_back(&l, b);
	// adding at the back must never move the head
	T("head does not change", l == a);
	// the old last node points to the new one and the new one ends the list
	T("new node is last", a->next == b && b->next == NULL);
	ft_lstadd_back(&l, c);
	// the function must walk to the real end and not stop at the head
	T("third node", b->next == c && c->next == NULL);
	t_lstfree(l);
	return (t_end());
}
