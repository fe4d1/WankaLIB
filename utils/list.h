#ifndef LIST_H
# define LIST_H

/* included by the ft_lst* tests instead of check.h, needs t_list */

# include "check.h"

t_list	*t_node(void *content);
void	t_lstfree(void *lst);

#endif
