/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executions_aux.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:21:10 by karocha-          #+#    #+#             */
/*   Updated: 2025/06/24 19:22:05 by karocha-         ###   ########.fr       */
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
