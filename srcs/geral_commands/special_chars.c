/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/23 13:09:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	piper(void)
{
	ft_printf("PIPE\n");
}

void	exit_status(char *line)
{
	/* int	i;

	i = 0;
	perror(mshell()->exit_status);
	strerror(mshell()->exit_status); */
	if (line)
		ft_printf("%i%s: command not found\n", mshell()->exit_status, line + 2);
	else
		ft_printf("%i: command not found\n", mshell()->exit_status);
}

void	handle_special(char **input, int index)
{
	if (ft_strcmp(input[index], "|") == 0)
		piper();
}
