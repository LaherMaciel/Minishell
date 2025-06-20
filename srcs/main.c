/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/16 17:47:34 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mshell(void)
{
	ft_free_export(NULL);
	ft_free_export(mshell()->env);
}

t_mshell	*mshell(void)
{
	static t_mshell	mshell;

	return (&mshell);
}

void	init_shell(char **env)
{
	mshell()->input = NULL;
	mshell()->input_value = 0;
	mshell()->redirected = 0;
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
	mshell()->exit_status = 0;
	mshell()->env = ft_calloc(sizeof(t_export), 1);
	if (!mshell()->env)
		exit(EXIT_FAILURE);
	mshell()->env = init_env(env);
	if (mshell()->env == NULL)
		handle_error_and_exit(-2, "Failed to create env struct");
	mshell()->expt = ft_calloc(sizeof(t_export), 1);
	if (!mshell()->expt)
		handle_error_and_exit(-2, "Failed to create export struct");
	mshell()->expt = init_export(env);
	mshell()->expt = export_sorter();
}

static void	receive_input(void)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = display_prompt(NULL);
		if (!line)
			break ;
	}
}

//update_shlvl();
int	main(int argv, char **argc, char **env)
{
	(void)argv;
	(void)argc;
	init_shell(env);
	receive_input();
	free_mshell();
	return (0);
}
/*
1 | 2|3 | 4   | 5 | 6
ls -a|grep mini | wc -l | cat >> test.txt
ls -a | grep mini | cat >> test.txt
cat test.txt
ls | wc -l
clear
pwd
cd ..
cd Minishell
env
export
export a=1
export
env
unset a
export 
env
echo $PATH
echo 1231234$USER=2
*/