/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:31:02 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/27 17:18:03 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_envs(char **commands, int i)
{
	char	*env_name;
	char	*env_value;
	int		j;

	j = 0;
	while (commands[i])
	{
		if (commands[i][0] == '$')
		{
			env_name = commands[i] + 1;
			env_value = getenv(env_name);
			if (env_value)
			{
				free(commands[i]);
				commands[i] = ft_strdup(env_value);
			}
			else
			{
				free(commands[i]);
				commands[i] = ft_strdup("");
			}
		}
		i++;
	}
}
