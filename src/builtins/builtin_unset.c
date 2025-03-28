/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:05:46 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/28 16:58:06 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	array_2d_len(char **env, char **cmd)
{
	int		i;
	int		j;
	int		remove;
	char	**key_value;
	char	*key;

	i = 0;
	remove = 0;
	while (env[i])
	{
		j = 0;
		while (cmd[j])
		{
			key_value = ft_split(env[i], '=');
			key = ft_strjoin(key_value[0], "=");
			if (ft_strncmp(env[0], key, ft_strlen(key)) == 0)
				remove++;
			free(key_value);
			free(key);
			j++;
		}
		i++;
	}
	return (i - remove + 1);
}

static char	**remove_env(char **envp, char **cmd)
{
	char	**new_envs;
	char	**env;
	int		i;
	int		j;

	new_envs = (char **)malloc((array_2d_len(envp, cmd) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (envp[i])
	{
		env = ft_split(envp[i], '=');
		if (ft_strcmp(env[0], cmd[1]) == 0 && !envp[i + 1])
			break ;
		else if (ft_strcmp(env[0], cmd[1]) == 0)
			i++;
		else
		{
			new_envs[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_envs[j] = NULL;
	return (new_envs);
}

int	builtin_unset(char **cmd)
{
	char	**envp;
	char	**new_envs;
	int		i;

	if (!cmd[1])
		return (1);
	i = 0;
	while (cmd[i])
	{
		env_error(cmd[i], "unset");
		i++;
	}
	envp = get_shell()->envp;
	new_envs = remove_env(envp, cmd);
	free_split(get_shell()->envp);
	get_shell()->envp = new_envs;
	return (EXIT_SUCCESS);
}
