/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:05:46 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/25 17:23:28 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **cmd, t_shell *shell)
{
	int		i;
	char	**envp;

	envp = shell->envp;
	i = 0;
	cmd = NULL;
	while (envp[i])
		i++;
	printf("envs: %d\n", i);
	return (1);
}
