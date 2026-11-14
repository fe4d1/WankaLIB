#include "check.h"

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
	T("empty list", l == a && a->next == NULL);
	ft_lstadd_back(&l, b);
	T("head does not change", l == a);
	T("new node is last", a->next == b && b->next == NULL);
	ft_lstadd_back(&l, c);
	T("third node", b->next == c && c->next == NULL);
	t_lstfree(l);
	return (t_end());
}
