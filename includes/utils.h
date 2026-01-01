/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:47:34 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:33:11 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char		*ft_itoa(int n);
void		ft_putnbr(int n);
bool		is_quote(char c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
void		ft_putchar(char c);
char		ft_toupper(char c);
void		ft_putstr(char *s);
char		ft_tolower(char c);
void		ft_putendl(char *s);
bool		is_whitespace(char c);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
t_list		*ft_lstnew(void *content);
int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
bool		is_var_char(char c, bool first);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_strcpy(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(const char *s1, const char *set);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *big, const char *little, size_t len);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif