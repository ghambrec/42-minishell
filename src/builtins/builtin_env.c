/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:58:56 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/25 16:05:14 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **cmd, t_shell *shell)
{
	int	i;

	if (cmd[1])
		return (ft_putendl_fd("call env without arguments", 1), 1);
	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}
