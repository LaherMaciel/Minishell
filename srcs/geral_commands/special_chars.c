/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:26:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/23 10:39:57 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	piper(void)
{
	
}

void	exit_status(void)
{
	ft_printf();
}

void	is_special(char **input)
{
	if (ft_strcmp(input, "|") == 0)
		piper();
	else
		exit_status();
}
