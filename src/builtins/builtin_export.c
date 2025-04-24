/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:38:33 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 16:05:03 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_declare_exports(void)
{
	int		i;
	int		j;
	char	**key_value;
	char	**envs;

	i = 0;
	envs = ft_sort_2d_strings(get_shell()->envp);
	while (envs[i])
	{
		key_value = ft_split(envs[i], '=');
		if (key_value[1])
		{
			printf("declare -x %s=\"%s\"", key_value[0], key_value[1]);
			j = 2;
			while (key_value[j])
				printf("=%s", key_value[j++]);
			printf("\n");
		}
		else
			printf("declare -x %s\n", key_value[0]);
		free(key_value);
		i++;
	}
}

static char	**add_export_env(char **envs, char *new_env)
{
	char	**new_envs;
	char	*check;
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
	if (ft_strchr(new_env, '='))
	{
		check = ft_strchr(new_env, '=');
		check++;
		if (*check == '\0')
		{
			check = ft_strtrim(new_env, "=");
			new_env = check;
			free(check);
		}
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
	return (free(key), free_split(key_value), false);
}

int	builtin_export(char **cmd)
{
	char	**envs;
	char	**temp;
	int		i;
	int		exit_code;
	int		exit_code_loop;

	exit_code = EXIT_SUCCESS;
	exit_code_loop = 0;
	if (!cmd[1])
		return (print_declare_exports(), EXIT_SUCCESS);
	envs = ft_sort_2d_strings(get_shell()->envp);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] && ft_strrchr(cmd[i], '='))
			exit_code_loop = env_error(cmd[i], "export");
		if (exit_code_loop > EXIT_SUCCESS)
			exit_code = exit_code_loop;
		if (exit_code_loop || env_exists(cmd[i], envs))
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
	return (exit_code);
}
