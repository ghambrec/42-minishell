/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:05:46 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:50:41 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	array_2d_len(char **env, char *cmd)
{
	int		i;
	int		remove;
	char	**key_value;
	char	*key;

	i = 0;
	remove = 0;
	while (env[i])
	{
		key_value = ft_split(env[i], '=');
		key = ft_strjoin(key_value[0], "=");
		if (ft_strncmp(cmd, key, ft_strlen(key)) == 0)
			remove++;
		free_split(key_value);
		free(key);
		i++;
	}
	return (i - remove);
}

static char	**remove_env(char **envp, char *cmd)
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
		if (ft_strcmp(env[0], cmd) == 0)
		{
			i++;
			free_split(env);
			continue ;
		}
		else
			new_envs[j++] = ft_strdup(envp[i++]);
		free_split(env);
	}
	new_envs[j] = NULL;
	return (new_envs);
}

int	builtin_unset(char **cmd)
{
	char	**envp;
	char	**new_envs;
	int		i;
	int		exit_code;
	int		exit_code_loop;

	exit_code = EXIT_SUCCESS;
	if (!cmd[1])
		return (exit_code);
	i = 1;
	envp = get_shell()->envp;
	while (cmd[i])
	{
		exit_code_loop = env_error(cmd[i], "unset");
		if (exit_code_loop > EXIT_SUCCESS)
			exit_code = exit_code_loop;
		if (exit_code_loop == 0)
		{
			new_envs = remove_env(envp, cmd[i]);
			free_split(envp);
			envp = new_envs;
		}
		i++;
	}
	return (get_shell()->envp = envp, exit_code);
}
