#include "list.h"
#include <stdlib.h>

/* helpers for the ft_lst* tests only: they need t_list, so they are not in
** check.c, a libft without t_list can still run every other test */

void	*__real_malloc(size_t n);

/* makes a node with the real malloc, so it never fails */
t_list	*t_node(void *content)
{
	t_list	*n;

	n = __real_malloc(sizeof(t_list));
	n->content = content;
	n->next = NULL;
	return (n);
}

/* frees a whole list and its contents */
void	t_lstfree(void *lst)
{
	t_list	*l;
	t_list	*next;

	l = lst;
	while (l)
	{
		next = l->next;
		free(l->content);
		free(l);
		l = next;
	}
}
