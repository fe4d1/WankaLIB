#include "check.h"
#include <stdlib.h>

static int	g_made;
static int	g_del;

/* f: new uppercased copy, counts the contents it makes */
static void	*upper(void *p)
{
	char	*s;

	g_made++;
	s = strdup(p);
	s[0] = toupper(s[0]);
	return (s);
}

/* counts its calls and frees the content */
static void	del(void *p)
{
	g_del++;
	free(p);
}

/* each malloc fails in turn: NULL and every content made by f deleted */
static void	fail_every_malloc(t_list *l)
{
	t_list	*m;
	int		i;
	int		hit;

	i = 0;
	while (i < 20)
	{
		g_made = 0;
		g_del = 0;
		t_set("malloc fails");
		fail_at(i);
		m = ft_lstmap(l, upper, del);
		hit = fail_hit();
		fail_at(-1);
		if (!hit)
		{
			t_lstfree(m);
			break ;
		}
		T("returns NULL when a malloc fails", m == NULL);
		T("every content made by f is deleted on failure", g_made == g_del);
		t_lstfree(m);
		i++;
	}
}

/* new list with f applied, original untouched, no leak on failure */
int	main(void)
{
	t_list	*l;
	t_list	*m;

	l = t_node(strdup("a"));
	l->next = t_node(strdup("b"));
	l->next->next = t_node(strdup("c"));
	m = ft_lstmap(l, upper, del);
	T("returns a list", m != NULL);
	T("same size", m && m->next && m->next->next && !m->next->next->next);
	T("f applied in order", m && !strcmp(m->content, "A")
		&& !strcmp(m->next->content, "B")
		&& !strcmp(m->next->next->content, "C"));
	T("new nodes and new contents", m != l && m->content != l->content);
	T("original list is not changed", !strcmp(l->content, "a")
		&& !strcmp(l->next->next->content, "c"));
	T("del not called when everything works", g_del == 0);
	t_lstfree(m);
	T("empty list returns NULL", ft_lstmap(NULL, upper, del) == NULL);
	fail_every_malloc(l);
	t_lstfree(l);
	return (t_end());
}
