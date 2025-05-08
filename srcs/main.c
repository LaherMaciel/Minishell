/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/08 21:57:44 by lahermaciel      ###   ########.fr       */
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
	mshell()->env = env;
	mshell()->expt = malloc(sizeof(t_export));
	if (!mshell()->expt)
		exit(EXIT_FAILURE);
	mshell()->expt = init_export(env);
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
	//signal_handler();
	receive_input();
	ft_free_array(mshell()->expt->var_name);
	ft_free_array(mshell()->expt->value);
	return (0);
}
