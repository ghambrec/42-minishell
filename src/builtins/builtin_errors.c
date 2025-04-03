/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:36:31 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/31 17:41:25 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_error(char *cmd, char *string)
{
	int	i;

	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd(string, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd(string, STDERR_FILENO);
			ft_putstr_fd(": `", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);	
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
