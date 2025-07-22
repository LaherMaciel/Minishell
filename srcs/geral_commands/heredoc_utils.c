/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:44:22 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/22 17:44:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quoted_delimiter(const char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (len >= 2 && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
			|| (delimiter[0] == '"' && delimiter[len - 1] == '"')))
		return (1);
	return (0);
}

char	*strip_quotes(const char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		|| (delimiter[0] == '"' && delimiter[len - 1] == '"'))
		return (ft_substr(delimiter, 1, len - 2));
	return (ft_strdup(delimiter));
}

int	check_delimiter(char *delimiter)
{
	if (!delimiter)
	{
		ft_fdprintf(STDERR_FILENO, "Minishell: syntax error near"
			" unexpected token `newline'\n");
		mshell()->exit_status = 2;
		return (0);
	}
	return (1);
}
