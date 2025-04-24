/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/04/24 16:50:10 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	receive_input(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(">> ");
		ft_printf("%s\n", line);
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
		{
			free(line);
			return ;
		}
		if (line)
			free(line);
	}
}

int	main(void)
{
	receive_input();
	return (0);
}
