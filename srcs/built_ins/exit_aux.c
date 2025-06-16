/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:22:59 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/16 15:55:52 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_status(char *line)
{
	if (line)
		ft_fdprintf(mshell()->outfile, "%i%s: command not found\n",
			mshell()->exit_status, line + 2);
	else
		ft_fdprintf(mshell()->outfile, "%i: command not found\n",
			mshell()->exit_status);
}

static int	ft_safe_atoi_aux2(long long result, int sign, bool *overflow)
{
	if (*overflow)
	{
		if (sign == 1)
			return (255);
		else if (sign == -1)
			return (-255);
		else
			return (0);
	}
	return ((int)(result * sign));
}

static char	*ft_safe_atoi_aux(char *ptr, int *sign)
{
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr == '-')
	{
		*sign = -1;
		ptr++;
	}
	else if (*ptr == '+')
		ptr++;
	return (ptr);
}

int	ft_safe_atoi(char *str, bool *overflow)
{
	long long	result;
	int			sign;
	char		*ptr;

	result = 0;
	sign = 1;
	ptr = str;
	*overflow = false;
	ptr = ft_safe_atoi_aux(ptr, &sign);
	while (ft_isdigit(*ptr))
	{
		if (((result * sign) == LONG_MIN / 10
				&& (*ptr - '0') > (LONG_MIN % 10) * -1)
			|| (result > (LONG_MAX - (*ptr - '0')) / 10 && sign == 1))
		{
			*overflow = true;
			break ;
		}
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	return (ft_safe_atoi_aux2(result, sign, overflow));
}
