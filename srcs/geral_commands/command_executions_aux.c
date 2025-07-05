/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:21:10 by karocha-          #+#    #+#             */
/*   Updated: 2025/07/05 21:16:00 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	aux_ex_cmnd_loop(int index, char **aux)
{
	aux = dupped_arr(index);
	if (aux)
	{
		run_command(aux,
			mshell()->infile, mshell()->outfile);
		ft_free_array(aux, 0);
	}
}
