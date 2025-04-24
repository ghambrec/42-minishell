/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:30:54 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:30:57 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_shell(t_shell *shell, bool call_exit)
{
	free_split(shell->envp);
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	if (call_exit == true)
		exit(shell->exit_code);
	return (shell->exit_code);
}
