/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:39 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/07 21:13:03 by lahermaciel      ###   ########.fr       */
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
	char	**export;
	int		*index;
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

//built-ins
int			builtin_cd(char *input);
int			builtin_pwd(void);
int			builtin_echo(char **input);
int			execute_builtin(char **input);
void		change_directory(const char *path);
void		init_environ(void);
void		ft_export(void);

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