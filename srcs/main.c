/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/04/25 15:29:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	receive_input(void)
{
	char	*line;

	while (1)
	{
		line = display_prompt(NULL);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strncmp(line, "exit", 0) == 0)
		{
			free(line);
			break ;
		}
		ft_printf("%s\n", line);
		free(line);
	}
}

int	main(void)
{
	receive_input();
	return (0);
}
