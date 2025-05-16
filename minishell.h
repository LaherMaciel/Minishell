/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:39 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/12 220:37 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <stdbool.h>

typedef struct s_export
{
	char	**value;
	char	**var_name;
}			t_export;

typedef struct s_mshell
{
	t_export	*expt;
	t_export	*env;

	char		**args;
	char		**aux_env;
	char		*line;
	char		*cmd;
	int			pid;
	int			status;
	int			infile;
	int			outfile;
}				t_mshell;

//prompt
char		*display_prompt(char *line);

//commands executions
char		*execute_commands(char *line);

//BUILT-INS
int			builtin_cd(char *input);
int			builtin_pwd(void);
int			builtin_echo(char **input);
int			execute_builtin(char **input);
void		change_directory(const char *path);
void		init_environ(void);
t_export	*init_export(char **env);
void		ft_export(void);
t_export	*export_sorter(void);
t_export	*add_to_export(char *str);
void		*ft_free_export(t_export *expt);
void		ft_unset(char *input);
char		**default_env(void);
t_export	*init_env(char **env);
void		ft_env(void);
t_export	*add_to_env(char *str);
char		*get_value(char *var_name);

//signals
void		signal_handler(void);

//utils
int			create_child_process(void);
void		handle_error_and_exit(int error, char *message);
char		*get_command_path(char *cmd, int flag);
void		handle_error_and_exit(int error, char *message);

//parser
char	**parser(char *input);
char	**split_out_quotes(char const *s, char c);
char	**ft_split3(char const *str, char *s, int i);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
char	**ft_split_minishell(char *input);
char	*ft_strjoin3(char *s1, char s2, int flag);

//main
t_mshell	*mshell(void);

#endif