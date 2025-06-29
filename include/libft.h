/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:19:13 by fsmyth            #+#    #+#             */
/*   Updated: 2025/02/14 18:51:29 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//	Part 1

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strdup(const char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

//	Part 2

char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//	Bonus

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *node);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *node);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// get_next_line

char	*get_next_line(int fd);

//	ft_printf

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);

// My own
void	free_split(char ***strings);
char	*ft_strndup(const char *s, size_t n);
int		ft_iswhitespace(char c);
int		ft_strwhitespace(char *str);
void	ft_lstdel_next(t_list *lst, void (*del)(void *));
int		ft_match_wc(char *str, char *wc, char wchar);
void	**ft_lst_to_arr(t_list *list);
void	ft_qsort(void **array, int left, int right,
			int (*cmp)(void *, void *));
int		ft_strcmp(char *s1, char *s2);
int		ft_strnum(char *str);
long	ft_strtol(char *nptr, char **endptr, int base);
int		ft_lst_exists(t_list *lst, void *match, int (*cmp)(void *, void *));
char	*ft_extend_line(char *line, char *extra);

#endif
