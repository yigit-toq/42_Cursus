/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:43:55 by ytop              #+#    #+#             */
/*   Updated: 2024/09/30 00:44:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./utils/get_next_line/get_next_line.h"

# include "./utils/printf/ft_dprintf.h"
# include "./utils/printf/ft_printf.h"

# include "./utils/parser/parser.h"

# ifndef GARBAGE_COLLECTOR
#  define GARBAGE_COLLECTOR 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstnew(void *content);

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstcopy(t_list *lst);

void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *));
void	ft_lstswap(t_list *lst1, t_list *lst2);

void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

void	del(void *content);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *str);

int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *b, int c, size_t len);

void	*ft_calloc(size_t count, size_t size);

void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

void	ft_bzero(void *s, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

char	*ft_itoa(int n);

char	**ft_split(char const *s, char c);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);

// Garbage Collector

void	clear_garbage(void);

void	gfree(void *address);

void	*galloc(size_t size);

void	*addgarbage(void *address);

t_list	**getgarbage(void);
#endif
