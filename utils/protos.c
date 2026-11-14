#include "libft.h"

/* every line fails to compile if the prototype differs from the subject */

int				(*p_isalpha)(int) = ft_isalpha;
int				(*p_isdigit)(int) = ft_isdigit;
int				(*p_isalnum)(int) = ft_isalnum;
int				(*p_isascii)(int) = ft_isascii;
int				(*p_isprint)(int) = ft_isprint;
size_t			(*p_strlen)(const char *) = ft_strlen;
void			*(*p_memset)(void *, int, size_t) = ft_memset;
void			(*p_bzero)(void *, size_t) = ft_bzero;
void			*(*p_memcpy)(void *, const void *, size_t) = ft_memcpy;
void			*(*p_memmove)(void *, const void *, size_t) = ft_memmove;
size_t			(*p_strlcpy)(char *, const char *, size_t) = ft_strlcpy;
size_t			(*p_strlcat)(char *, const char *, size_t) = ft_strlcat;
int				(*p_toupper)(int) = ft_toupper;
int				(*p_tolower)(int) = ft_tolower;
char			*(*p_strchr)(const char *, int) = ft_strchr;
char			*(*p_strrchr)(const char *, int) = ft_strrchr;
int				(*p_strncmp)(const char *, const char *, size_t) = ft_strncmp;
void			*(*p_memchr)(const void *, int, size_t) = ft_memchr;
int				(*p_memcmp)(const void *, const void *, size_t) = ft_memcmp;
char			*(*p_strnstr)(const char *, const char *, size_t) = ft_strnstr;
int				(*p_atoi)(const char *) = ft_atoi;
void			*(*p_calloc)(size_t, size_t) = ft_calloc;
char			*(*p_strdup)(const char *) = ft_strdup;

char			*(*p_substr)(char const *, unsigned int, size_t) = ft_substr;
char			*(*p_strjoin)(char const *, char const *) = ft_strjoin;
char			*(*p_strtrim)(char const *, char const *) = ft_strtrim;
char			**(*p_split)(char const *, char) = ft_split;
char			*(*p_itoa)(int) = ft_itoa;
char			*(*p_strmapi)(char const *, char (*)(unsigned int, char))
	= ft_strmapi;
void			(*p_striteri)(char *, void (*)(unsigned int, char *))
	= ft_striteri;
void			(*p_putchar_fd)(char, int) = ft_putchar_fd;
void			(*p_putstr_fd)(char *, int) = ft_putstr_fd;
void			(*p_putendl_fd)(char *, int) = ft_putendl_fd;
void			(*p_putnbr_fd)(int, int) = ft_putnbr_fd;

t_list			*(*p_lstnew)(void *) = ft_lstnew;
void			(*p_lstadd_front)(t_list **, t_list *) = ft_lstadd_front;
unsigned int	(*p_lstsize)(t_list *) = ft_lstsize;
t_list			*(*p_lstlast)(t_list *) = ft_lstlast;
void			(*p_lstadd_back)(t_list **, t_list *) = ft_lstadd_back;
void			(*p_lstdelone)(t_list *, void (*)(void *)) = ft_lstdelone;
void			(*p_lstclear)(t_list **, void (*)(void *)) = ft_lstclear;
void			(*p_lstiter)(t_list *, void (*)(void *)) = ft_lstiter;
t_list			*(*p_lstmap)(t_list *, void *(*)(void *), void (*)(void *))
	= ft_lstmap;

_Static_assert(sizeof(t_list) == 2 * sizeof(void *),
	"t_list must have exactly content and next");

void	*check_t_list(void)
{
	struct s_list	node;
	void			**content;
	t_list			**next;

	content = &node.content;
	next = &node.next;
	return ((void *)content == (void *)next ? NULL : &p_lstmap);
}
