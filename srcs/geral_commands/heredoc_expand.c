/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:43:18 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/07/23 13:53:43 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_expand_prefix(char **result, const char *line,
		size_t last_pos, size_t len)
{
	char	*prefix;

	if (len > 0)
	{
		prefix = ft_substr(line + last_pos, 0, len);
		if (!prefix)
		{
			free(*result);
			return (0);
		}
		*result = ft_strjoin2(*result, prefix, 1);
		free(prefix);
		if (!*result)
			return (0);
	}
	return (1);
}

static int	handle_expand_var(char **result, char *var_start, char *var_end)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_substr(var_start + 1, 0, var_end - (var_start + 1));
	if (!var_name)
	{
		free(*result);
		return (0);
	}
	var_value = get_value(var_name);
	free(var_name);
	if (var_value)
	{
		*result = ft_strjoin2(*result, var_value, 1);
		free(var_value);
		if (!*result)
			return (0);
	}
	return (1);
}

static int	handle_expand_suffix(char **result, const char *line,
		size_t last_pos)
{
	char	*prefix;

	if (line[last_pos])
	{
		prefix = ft_strdup(line + last_pos);
		if (!prefix)
		{
			free(*result);
			return (0);
		}
		*result = ft_strjoin2(*result, prefix, 1);
		free(prefix);
		if (!*result)
			return (0);
	}
	return (1);
}

static int	process_variable_expansion(char **result, const char *line,
		size_t *last_pos)
{
	char	*var_start;
	char	*var_end;
	size_t	len;

	var_start = ft_strchr(line + *last_pos, '$');
	if (!var_start)
		return (1);
	len = var_start - (line + *last_pos);
	if (!handle_expand_prefix(result, line, *last_pos, len))
		return (0);
	var_end = var_start + 1;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	if (var_end == var_start + 1)
	{
		*result = ft_strjoin2(*result, "$", 1);
		if (!*result)
			return (0);
		*last_pos = var_end - line;
		return (2);
	}
	if (!handle_expand_var(result, var_start, var_end))
		return (0);
	*last_pos = var_end - line;
	return (1);
}

char	*expand_heredoc_vars(const char *line)
{
	char	*result;
	size_t	last_pos;
	int		status;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	if (!line[0])
		return (result);
	last_pos = 0;
	while (line[last_pos] && ft_strchr(line + last_pos, '$'))
	{
		status = process_variable_expansion(&result, line, &last_pos);
		if (status == 0)
			return (NULL);
		if (status == 2)
			continue ;
	}
	if (!handle_expand_suffix(&result, line, last_pos))
		return (NULL);
	return (result);
}
