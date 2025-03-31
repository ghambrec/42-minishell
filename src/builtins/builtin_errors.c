/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:36:31 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/31 14:02:53 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_error(char *cmd, char *string)
{
	int	i;

	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (printf("%s: `%s': not a valid identifier\n", string, cmd),
			EXIT_SUCCESS);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (printf("%s: `%s': not a valid identifier\n", string, cmd),
				EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}
