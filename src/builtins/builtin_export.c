/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:38:33 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/28 13:28:40 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_declare_exports(char **envs)
{
	int		i;
	char	**key_value;

	i = 0;
	while (envs[i])
	{
		key_value = ft_split(envs[i], '=');
		printf("declare -x %s=\"%s\"\n", key_value[0], key_value[1]);
		free(key_value);
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
	char	**temp;
	int		i;

	envs = ft_sort_2d_strings(get_shell()->envp);
	if (!cmd[1])
		return (print_declare_exports(envs), 0);
	i = 1;
	while (cmd[i])
	{
		temp = add_export_env(envs, cmd[i]);
		free_split(envs);
		envs = temp;
		i++;
	}
	get_shell()->envp = envs;
	return (0);
}
