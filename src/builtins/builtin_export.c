/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:38:33 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/27 17:44:24 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_declare_exports(char **envs)
{
	int		i;

	i = 0;
	while (envs[i])
	{
		printf("declare -x %s\n", envs[i]);
		i++;
	}
}

char	**add_export_env(char **envs, char *new_env)
{
	char	**new_envs;
	int		i;
	int		j;

	i = 0;
	while (envs[i])
		i++;
	new_envs = (char **)malloc((i + 2) * sizeof(char *));
	j = 0;
	while (envs[j])
	{
		new_envs[j] = ft_strdup(envs[j]);
		j++;
	}
	new_envs[j] = ft_strdup(new_env);
	new_envs[j + 1] = NULL;
	return (new_envs);
}

int	builtin_export(char **cmd)
{
	char	**envs;

	envs = get_shell()->envp;
	if (!cmd[1])
		return (print_declare_exports(envs), 0);
		get_shell()->envp = add_export_env(envs, cmd[1]);
	free_split(envs);
	return (0);
}
