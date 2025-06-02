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

typedef struct s_child_pid
{
	pid_t				pid;
	struct s_child_pid	*next;
}					t_child_pid;

typedef struct s_mshell
{
	t_export	*expt;
	t_export	*env;

	t_child_pid	*child_pids;
	int			num_children;
	int			exit_status;
	char		**input;
	int			*input_value;
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
int			redirection_operators_handler(int index);
int			handle_special(int index);
void		exit_status(char *line);
void		run_command(char **args, int infile, int outfile);
void		execute_simple_command(char **args, int infile, int outfile);
void		add_child_pid(pid_t pid);
void		free_child_pids(void);

//BUILT-INS
int			builtin_cd(char *input);
int			builtin_pwd(void);
int			builtin_echo(char **input);
int			execute_builtin(char **input);
void		change_directory(char *path);
void		init_environ(void);
t_export	*init_export(char **env);
void		ft_export(char **input);
t_export	*export_sorter(void);
t_export	*add_to_export(char *str);
void		*ft_free_export(t_export *expt);
void		ft_unset(char **input, int index);
char		**default_env(void);
t_export	*init_env(char **env);
void		ft_env(char **input);
t_export	*add_to_env(char *str);
char		*get_value(char *var_name);
char		*get_varname(char *value);
char		*get_varname2(char *var_name);
void		builtins(char **input);

//signals
void		sigint_handler(int sig);

//utils
int			create_child_process(void);
void		handle_error_and_exit(int error, char *message);
char		*get_command_path(char *cmd);
void		handle_error_and_exit(int error, char *message);
t_export	*update_var(t_export *env, char **splitted);
int			high_priority(void);
void		rm_index(int index);
void		rm_indexs(int index1, int index2);
char		**dupped_arr(int index);
void		reset_fds(void);
void		free_resources(void);
char		**pipe_dupped_arr(int index);

//parser
void		parser(char *input);
char		**split_out_quotes(char const *s, char c);
char		**ft_split3(char const *str, char *s, int i);
char		*ft_substr2(char const *s, unsigned int start, size_t len);
char		**ft_split_minishell(char *input);
char		*ft_strjoin3(char *s1, char s2, int flag);
void		about_quotes(char *input, int *quote, size_t i);
char		**add_current(char **res, char **cur, int *k);
int			its_what(char *str);
void		set_inputvalue(void);
int			is_special(char *str);
int			is_builtin(char *str);
int			is_redirect(char *str);

//main
t_mshell	*mshell(void);
void		free_mshell(void);

#endif