/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:36:31 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/28 16:30:58 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_error(char *cmd, char *string)
{
	int	i;

	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (printf("%s: `%s': not a valid identifier\n", string, cmd),
			true);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (printf("%s: `%s': not a valid identifier\n", string, cmd),
				true);
		i++;
	}
	return (false);
}
