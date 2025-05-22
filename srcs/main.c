/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/22 19:45:05 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mshell(void)
{
	ft_free_export(NULL);
	ft_free_export(mshell()->env);
	ft_free_array(mshell()->aux_env, 0);
}

t_mshell	*mshell(void)
{
	static t_mshell	mshell;

	return (&mshell);
}

void	init_shell(char **env)
{
	mshell()->infile = STDIN_FILENO;
	mshell()->outfile = STDOUT_FILENO;
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
	mshell()->aux_env = NULL;
	mshell()->expt = export_sorter();
}

static void	receive_input(void)
{
	char	*line;

	while (1)
	{
		line = display_prompt(NULL);
		if (!line)
			break ;
	}
}

int	main(int argv, char **argc, char **env)
{
	(void)argv;
	(void)argc;
	init_shell(env);
	receive_input();
	free_mshell();
	return (0);
}
