/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <laherwpayotmaciel@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:20:26 by lwencesl          #+#    #+#             */
/*   Updated: 2023/02/06 17:47:13 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>

/**
 * * All the other functions are declared on the `ft_printf.c` file I'm doing
 *   that to prevent me for seeing does functions when using the `ft_printf.c`
 *   on another project
*/

// COLOR CODES
# define CLEAR "\033c"
# define RED        "\033[1;31m"
# define GREEN      "\033[1;32m"
# define YELLOW     "\033[1;33m"
# define BLUE       "\033[1;34m"
# define MAGENTA    "\033[1;35m"
# define CYAN       "\033[1;36m"
# define WHITE      "\033[1;37m"
# define GRAY       "\033[1;90m"
# define ORANGE     "\033[38;5;208m"
# define PURPLE     "\033[38;5;129m"
# define PINK       "\033[38;5;205m"
# define LIME       "\033[38;5;154m"
# define TEAL       "\033[38;5;30m"
# define LAVENDER   "\033[38;5;183m"
# define GOLD       "\033[38;5;220m"
# define MAROON     "\033[38;5;88m"
# define DEFAULT_COLOR "\033[0m"
# define BOLTED_DEFAULT_COLOR "\033[1;0m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

//Part 1
size_t		ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int a);
int			ft_isalpha(int c);
int			ft_isascii(int a);
int			ft_isdigit(int i);
int			ft_isprint(int a);
void		*ft_memchr(void *str, int c, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
char		*ft_strchr(const char *str, int c);
size_t		ft_strlcat(char *dest, const char *src, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *a);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *str, int c);
int			ft_tolower(int a);
int			ft_toupper(int c);

//Part 1.5
void		*ft_calloc(size_t n, size_t size);
char		*ft_strdup(const char *s);

//Part 2
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *str, char c);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(const char *str, const char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

//Bonus
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//ft_printf
int			ft_printf(const char *format, ...);
//ft_fdprintf
int			ft_fdprintf(int fd, const char *format, ...);
//get_next_line
char		*get_next_line(int fd);

//extras
int			ft_strcmp(const char *str1, const char *str2);
size_t		ft_arraylen(char **a);
char		**ft_split2(char const *str, char c);
char		*ft_substr2(char const *s, unsigned int start, size_t len);
char		*ft_strjoin2(char *s1, char *s2, int flag);
void		*ft_free_array(char **strstr, size_t len);
char		**ft_append_to_array(char **array, size_t arraylen,
				char *str, int flag);
void		ft_swap(char **a, char **b, int flag);
char		**ft_rm_from_array(char **array, size_t arraylen, size_t index);
char		*ft_strcpy(char *dest, char *src);
char		**ft_append_to_array2(char **array, size_t arraylen,
				char *str, int flag);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void		*ft_realloc_and_clear(void *ptr, size_t old_size, size_t new_size);
int			ft_isspace(int c);

char		*ft_putchar_shell(int c);
char		*ft_putstr_shell(char *str);
char		*ft_putnbr_shell(long long int number, char *result);
char		*ft_putnbr_u_shell(unsigned long long int number, char *result);
char		*ft_puthex_shell(unsigned int number, char variable, char *result);
char		*ft_putptr_shell(unsigned long long ptr, char *result);
char		*ft_format_shell(va_list args, const char variable);
int			ft_printf_shell(const char *str, ...);
int			ft_div_num_base_shell(long int number, int base);
char		*ft_putchar_shell(int c);

// FD_PRINTF
char		*ft_fdputstr_shell(int fd, char *s);
char		*ft_fdputchr_shell(int fd, char s);
char		*ft_fdputnbr_shell(int fd, double nbr, char *base, double size);
char		*fdputpoint_shell(int fd, unsigned long long nbr, char *base,
				unsigned long long size);
int			ft_fdprintf_shell(int fd, const char *format, ...);

#endif