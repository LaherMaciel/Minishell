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
	int			*quoted;
	char		**input;
	int			*input_v;
	int			redirected;
	int			pid;
	int			status;
	int			infile;
	int			outfile;
	int			heredoc;
}				t_mshell;

typedef struct s_pars_lst
{
	char				*content;
	int					quoted;
	struct s_pars_lst	*next;
}					t_pars_lst;

typedef struct s_parsing
{
	int		k;
	size_t	i;
	int		quote;
	t_list	result;
}			t_parsing;

//prompt
char		*display_prompt(char *line);
char		*get_command_path(char *cmd);
char		*search_command_in_path(char *cmd, char *path_env);
int			check_executable(const char *cmd, int flag);

//commands executions
void		execute_commands(char *line);
int			redirection_operators_handler(int index);
int			pipe_handler(int index);
void		exit_status(char *line);
void		run_command(char **args, int infile, int outfile);
void		execute_simple_command(char **args, int infile, int outfile);
void		add_child_pid(pid_t pid);
void		free_child_pids(void);
int			handle_heredoc(char *delimiter, int fd[2], int is_quoted);
void		aux_ex_cmnd_loop(int index);
char		*expand_heredoc_vars(const char *line);
void		wait_for_childs(void);

//BUILT-INS
int			builtin_cd(char *input);
int			builtin_pwd(void);
int			builtin_echo(char **input);
int			execute_builtin(char **input);
char		*change_directory(char *path);
void		init_environ(void);
t_export	*init_export(char **env);
void		ft_export(char **input);
t_export	*export_sorter(void);
t_export	*add_to_export(char *str);
void		*ft_free_export_env(t_export *expt);
void		ft_unset(char **input, int index);
char		**default_env(void);
t_export	*init_env(char **env);
void		ft_env(char **input);
t_export	*add_to_env(char *str);
char		*get_value(char *var_name);
int			get_value2(char *var_name);
int			builtins(char **input);
void		builtin_exit(char **input);
void		update_shlvl(void);
int			check_var_name(char *var_name);
void		start_no_env(void);
void		update_(char *command);
bool		echo_parse_n_flag(char **input, int *i);
void		echo_print_args(char **input, int i);
int			is_valid_identifier(const char *str);
void		export_error(const char *str);
t_export	*adder(t_export *env, char *name, char *value, int flag);

//signals
void		sigint_handler(int sig);
void		sig_heredoc(int sig);

//utils
int			create_child_process(void);
void		handle_error_and_exit(int error, char *message);
void		handle_error_and_exit(int error, char *message);
t_export	*update_var(t_export *env, char *name, char *value);
int			high_priority(void);
void		rm_index(int index);
void		rm_indexs(int index1, int index2);
char		**dupped_arr(int index);
void		reset_fds(void);
void		free_resources(void);
char		**pipe_dupped_arr(int index);
int			word_size(char *str);
char		*get_varname(char *value);
char		*get_varname2(char *var_name);
void		exp_loop(int i, char **input, char	*aux);
bool		is_valid_exit_code(const char *str);
int			normalize_exit_status(int status);
int			ft_safe_atoi(char *str, bool *overflow);
void		clear_input(char **aux);
void		reset_outfile(int fd);
void		reset_infile(int fd);
void		clean_exit(int exit_status);
void		clean_resource(void);
void		print_input(int flag, size_t i);
void		clean_trash(void);
char		*free_if_fail(char **env, char **args, char *cmd_path);
int			check_bad_specials(void);

//parser
void		parser(char *input);
char		**split_out_quotes(char const *s, char c);
char		**ft_split3(char const *str, char *s, int i);
char		*ft_substr2(char const *s, unsigned int start, size_t len);
char		**ft_split_minishell(char *input);
char		*ft_strjoin3(char *s1, char s2, int flag);
void		about_quotes(char *input, t_parsing *counts);
char		**add_current(char **res, char **cur, int *k);
int			its_what(int index);
void		set_inputvalue(int index);
void		set_inputvalues(int index1, int index2);
int			is_special(char *str);
int			is_builtin(char *str);
int			is_redirect(char *str);
void		ft_split_shell_lst(char *input);
int			ft_lstsize_shell(t_pars_lst *lst);
t_pars_lst	*ft_lstnew_shell(void *content, int quoted);
t_pars_lst	*ft_lstlast_shell(t_pars_lst *lst);
void		ft_lstdelone_shell(t_pars_lst *lst, void (*del)(void*));
void		ft_lstclear_shell(t_pars_lst **lst, void (*del)(void*));
void		ft_lstadd_back_shell(t_pars_lst **lst, t_pars_lst *new);
void		add_token_lst(t_pars_lst **lst, char **cur, char *str);
void		aux_token(char **content, char *input, t_parsing *counts);
void		list_to_mshell(t_pars_lst *lst, size_t i);
void		print_pars_node(t_pars_lst *node, int index);
void		print_pars_list(t_pars_lst *lst);
void		add_operator(t_pars_lst **lst, char *type, t_parsing *counts);
int			dollar_sign_lst(char **cur, char *input, t_parsing *counts);
t_parsing	*process_token_lst(t_pars_lst **lst,
				t_pars_lst **new_node, char *input, t_parsing *counts);

//main
t_mshell	*mshell(void);
void		free_mshell(void);

#endif