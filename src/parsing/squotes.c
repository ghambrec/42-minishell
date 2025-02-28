/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:43:07 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/28 22:58:06 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	merge_single_quotes(char **commands, int i)
{
	char	*merged;
	char	*start;
	int		j;

	start = commands[i] + 1;
	merged = ft_strdup(start);
	if (handle_immediate_end(commands, i, merged))
		return ;
	free(commands[i]);
	j = i + 1;
	while (commands[j] && !ft_strchr(commands[j], 39))
	{
		merged = ft_strjoin(ft_strjoin(merged, " "),
				commands[j] + (commands[j][1] == 39));
		free(commands[j++]);
	}
	if (commands[j])
	{
		*ft_strchr(commands[j], 39) = '\0';
		merged = ft_strjoin(ft_strjoin(merged, " "), commands[j]);
		free(commands[j++]);
	}
	commands[i] = merged;
	shift_command_left(commands, i, j);
}
