/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:30:44 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:10:44 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	init_signals();
	shell = get_shell();
	if (argc == 1)
	{
		shell->envp = ft_strarr_dup(envp);
		if (!shell->envp)
			return (EXIT_FAILURE);
		shell->exit_code = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
