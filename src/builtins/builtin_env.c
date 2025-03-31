/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:58:56 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/27 16:37:42 by ghambrec         ###   ########.fr       */
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