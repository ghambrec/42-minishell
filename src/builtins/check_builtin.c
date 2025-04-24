/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:32:31 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:52:04 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (true);
	else
		return (false);
}
