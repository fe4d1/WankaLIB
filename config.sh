# edit this file to adapt the tester

LIBFT=../libft

FLAGS="-Wall -Wextra -Werror"

PART1="ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen
ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_toupper
ft_tolower ft_strchr ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr
ft_atoi ft_calloc ft_strdup"

PART2="ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi
ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd"

PART3="ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back
ft_lstdelone ft_lstclear ft_lstiter ft_lstmap"

EXTRA_FILES="Makefile libft.h README.md"

# external functions allowed per function (everything else is forbidden)
declare -A ALLOWED=(
	[ft_calloc]="malloc"
	[ft_strdup]="malloc"
	[ft_substr]="malloc"
	[ft_strjoin]="malloc"
	[ft_strtrim]="malloc"
	[ft_split]="malloc free"
	[ft_itoa]="malloc"
	[ft_strmapi]="malloc"
	[ft_putchar_fd]="write"
	[ft_putstr_fd]="write"
	[ft_putendl_fd]="write"
	[ft_putnbr_fd]="write"
	[ft_lstnew]="malloc"
	[ft_lstdelone]="free"
	[ft_lstclear]="free"
	[ft_lstmap]="malloc free"
)

README_LINE='^[*_]This project has been created as part of the 42 curriculum by .+[*_]$'
README_SECTIONS="Description Instructions Resources"
