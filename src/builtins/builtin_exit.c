/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:49 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:50:27 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	full_numeric(char *str)
{
	if (!str)
		return (false);
	if (ft_strlen(str) == 0)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	builtin_exit(char **cmd)
{
	if (cmd[1] && cmd[2] && full_numeric(cmd[1]) == true)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	if (cmd[1])
	{
		if (full_numeric(cmd[1]) == true)
			get_shell()->exit_code = ft_atoi(cmd[1]);
		else
		{
			get_shell()->exit_code = 255;
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		}
	}
	else
		ft_putendl_fd("exit", STDERR_FILENO);
	get_shell()->exit_code %= 256;
	free_ast(get_shell()->ast);
	exit_shell(get_shell(), true);
}
