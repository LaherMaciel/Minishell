/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:28:44 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/02 16:09:29 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* static void	env_err(char input)
{
	
	exit (0);
}

void	parse_env(char *input)
{
	int	i;

	i = -1;
	if (!isalpha(input[0]))
		return (env_err(input[0]));
} */

int	word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}
