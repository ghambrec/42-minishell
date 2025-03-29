/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:38:33 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/29 14:57:18 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_declare_exports(void)
{
	int		i;
	char	**key_value;
	char	**envs;

	i = 0;
	envs = ft_sort_2d_strings(get_shell()->envp);
	while (envs[i])
	{
		key_value = ft_split(envs[i], '=');
		if (key_value[1])
			printf("declare -x %s=\"%s\"\n", key_value[0], key_value[1]);
		else
			printf("declare -x %s\n", key_value[0]);
		free(key_value);
		i++;
	}
}

static char	**add_export_env(char **envs, char *new_env)
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

static bool	check_env(char **key_value, char **envp, char *key, char *new_env)
{
	if (!key_value[1] && ft_strncmp(key, *envp, ft_strlen(*envp)) == 0)
		return (true);
	else if (ft_strncmp(key, *envp, ft_strlen(*envp)) == 0)
	{
		new_env = ft_strjoin(key, key_value[1]);
		free(*envp);
		*envp = new_env;
		return (true);
	}
	else if (ft_strncmp(*envp, key, ft_strlen(key)) == 0)
	{
		if (!key_value[1])
		{
			new_env = ft_strdup(key_value[0]);
			free(*envp);
			*envp = new_env;
			return (true);
		}
		new_env = ft_strjoin(key, key_value[1]);
		free(*envp);
		*envp = new_env;
		return (true);
	}
	return (false);
}

static bool	env_exists(char *cmd, char **envp)
{
	char	**key_value;
	char	*key;
	char	*new_env;
	int		i;

	key_value = ft_split(cmd, '=');
	key = ft_strjoin(key_value[0], "=");
	new_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (check_env(key_value, &envp[i], key, new_env))
			return (free(key), free_split(key_value), true);
		i++;
	}
	return (false);
}

int	builtin_export(char **cmd)
{
	char	**envs;
	char	**temp;
	int		i;

	if (!cmd[1])
		return (print_declare_exports(), EXIT_SUCCESS);
	envs = ft_sort_2d_strings(get_shell()->envp);
	i = 1;
	while (cmd[i])
	{
		if (env_error(cmd[i], "export") || env_exists(cmd[i], envs))
		{
			i++;
			continue ;
		}
		temp = add_export_env(envs, cmd[i]);
		free_split(envs);
		envs = temp;
		i++;
	}
	get_shell()->envp = envs;
	return (EXIT_SUCCESS);
}
