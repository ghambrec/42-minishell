/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:58:56 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:34:09 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **cmd)
{
	int	i;

	if (cmd[1])
	{
		ft_putendl_fd("No options or arguments allowed!", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (get_shell()->envp[i])
	{
		printf("%s\n", get_shell()->envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
