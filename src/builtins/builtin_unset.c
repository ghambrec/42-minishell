/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:05:46 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/26 13:04:45 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **cmd)
{
	int		i;
	int		j;
	char	**envp;
	char	**env;
	char	**new_envs;

	envp = get_shell()->envp;
	env = NULL;
	i = 0;
	j = 0;
	while (envp[i])
		i++;
	new_envs = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env = ft_split(envp[i], '=');
		if (ft_strcmp(env[0], cmd[1]) == 0)
			i++;
		else
		{
			new_envs[j] = envp[i];
			j++;
		}
		i++;
	}
	new_envs[j] = NULL;
	free_split(get_shell()->envp);
	get_shell()->envp = new_envs;
	return (1);
}
