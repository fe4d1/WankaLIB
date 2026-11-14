#include "check.h"

int	main(void)
{
	t_list	*l;
	t_list	*a;
	t_list	*b;

	l = NULL;
	a = t_node(strdup("a"));
	b = t_node(strdup("b"));
	ft_lstadd_front(&l, a);
	T("empty list", l == a && a->next == NULL);
	ft_lstadd_front(&l, b);
	T("new node becomes the head", l == b);
	T("old head is second", b->next == a && a->next == NULL);
	t_lstfree(l);
	return (t_end());
}
