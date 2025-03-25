/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:38:33 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/25 14:30:18 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_declare_exports(t_shell *shell)
{
	char	**temp;
	int		i;

	temp = shell->envp;
	i = 0;
	while (temp[i])
	{
		printf("declare -x %s\n", temp[i]);
		i++;
	}
}

int	builtin_export(char **cmd, t_shell *shell)
{
	if (!cmd[1])
		print_declare_exports(shell);
	return (0);
}
