/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:39 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/12 21:36:25 by lahermaciel      ###   ########.fr       */
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

	char		**args;
	char		**env;
	char		*line;
	char		*cmd;
	int			pid;
	int			status;
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
void		ft_unset(char **input, int index);

//signals
void		signal_handler(void);

//utils
int			create_child_process(void);
void		handle_error_and_exit(int error, char *message);
char		*get_command_path(char *cmd, int flag);
void		handle_error_and_exit(int error, char *message);

//main
t_mshell	*mshell(void);

#endif