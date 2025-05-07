/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:17:03 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/07 20:40:01 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
void	init_environ(void)
{
	extern char	**environ;
}
 */
void	ft_export(void)
{
	ft_printf("Environment variables:\n\n\n%t\n", mshell()->export);
}
