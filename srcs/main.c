/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/26 12:35:17 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mshell	*mshell(void)
{
	static t_mshell	mshell;

	return (&mshell);
}

void	init_shell(char **env)
{
	mshell()->input = NULL;
	mshell()->input_v = 0;
	mshell()->redirected = 0;
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
	mshell()->exit_status = 0;
	mshell()->env = ft_calloc(sizeof(t_export), 1);
	if (!mshell()->env)
		clean_exit(EXIT_FAILURE);
	mshell()->expt = ft_calloc(sizeof(t_export), 1);
	if (!mshell()->expt)
		handle_error_and_exit(-2, "Failed to create export struct");
	if (!env || !env[0])
		start_no_env();
	else
	{
		mshell()->env = init_env(env);
		if (mshell()->env == NULL)
			handle_error_and_exit(-2, "Failed to create env struct");
		mshell()->expt = init_export(env);
		if (mshell()->expt == NULL)
			handle_error_and_exit(-2, "Failed to create export struct");
		mshell()->expt = export_sorter();
	}
}

int	main(int argv, char **argc, char **env)
{
	char	*line;

	(void)argv;
	(void)argc;
	line = NULL;
	init_shell(env);
	if (isatty(STDIN_FILENO))
		display_prompt(line);
	else
	{
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			execute_commands(line);
			line = get_next_line(STDIN_FILENO);
		}
	}
	free_mshell();
	return (0);
}
