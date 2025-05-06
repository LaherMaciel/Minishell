/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/05 22:09:50 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mshell	*mshell(void)
{
	static t_mshell	mshell;

	return (&mshell);
}

void	init_shell()
{
	mshell()->env = NULL;
}

static void	receive_input(char **env)
{
	char	*line;

	ft_printf("%t\n", mshell()->env);
	while (1)
	{
		line = display_prompt(NULL, env);
		if (!line)
			break ;
	}
}

int	main(int argv, char **argc, char **env)
{
	(void)argv;
	(void)argc;
	init_shell();
	mshell()->env = env;
	//signal_handler();
	receive_input(env);
	return (0);
}
