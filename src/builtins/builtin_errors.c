/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:36:31 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 14:59:35 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_error(char *prog, char *key)
{
	ft_putstr_fd(prog, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	env_error(char *key, char *prog)
{
	int	i;

	if (ft_strcmp(prog, "unset") == 0 && ft_strchr(key, '='))
	{
		print_env_error(prog, key);
		return (EXIT_FAILURE);
	}
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		print_env_error(prog, key);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			print_env_error(prog, key);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
