#include "list.h"
#include <stdlib.h>

/* node keeps the pointer (no copy), next is NULL */
int	main(void)
{
	char	*s = "hello";
	t_list	*n;

	n = ft_lstnew(s);
	// a normal call must give a node
	T("returns a node", n != NULL);
	// the subject says content is the parameter, the string is not copied
	T("content is the same pointer (no copy)", n && n->content == s);
	// next must be set, malloc does not give zeroed memory
	T("next is NULL", n && n->next == NULL);
	free(n);
	n = ft_lstnew(NULL);
	// NULL is a valid content
	T("NULL content still makes a node", n != NULL && n->content == NULL
		&& n->next == NULL);
	free(n);
	// when malloc fails lstnew must return NULL and not write in it
	MFAIL("malloc fails", ft_lstnew(s), free);
	return (t_end());
}
