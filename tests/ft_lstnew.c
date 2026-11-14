#include "check.h"
#include <stdlib.h>

int	main(void)
{
	char	*s = "hello";
	t_list	*n;

	n = ft_lstnew(s);
	T("returns a node", n != NULL);
	T("content is the same pointer (no copy)", n && n->content == s);
	T("next is NULL", n && n->next == NULL);
	free(n);
	n = ft_lstnew(NULL);
	T("NULL content still makes a node", n != NULL && n->content == NULL
		&& n->next == NULL);
	free(n);
	MFAIL("malloc fails", ft_lstnew(s), free);
	return (t_end());
}
