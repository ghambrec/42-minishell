/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:52:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 14:56:55 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(char *env_key)
{
	char	**split_env;
	char	**envs;
	char	*env_value;
	char	*key;
	int		i;

	envs = get_shell()->envp;
	split_env = NULL;
	key = ft_strjoin(env_key, "=");
	i = 0;
	while (envs[i])
	{
		if (ft_strncmp(envs[i], key, ft_strlen(key)) == 0)
			split_env = ft_split(envs[i], '=');
		i++;
	}
	if (split_env == NULL)
		return ("");
	env_value = ft_strdup(split_env[1]);
	free_split(split_env);
	free(key);
	return (env_value);
}
