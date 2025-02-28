/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:01 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/28 23:45:34 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_quotes(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		// printf("commands Nbr: %d -> %s\n", i, commands[i]);
		if (commands[i][0] == 39)
			merge_single_quotes(commands, i);
		else if (commands[i][0] == '"')
			merge_quotes(commands, i);
		i++;
	}
}

bool	handle_immediate_end(char **commands, int i, char *merged)
{
	char	*end_quote;

	end_quote = ft_strchr(merged, '"');
	if (!end_quote)
		end_quote = ft_strchr(merged, 39);
	if (end_quote)
	{
		*end_quote = '\0';
		free(commands[i]);
		commands[i] = merged;
		return (true);
	}
	else
		return (false);
}

void	shift_command_left(char **commands, int i, int j)
{
	int	k;

	k = i + 1;
	while (commands[j])
		commands[k++] = commands[j++];
	commands[k] = NULL;
}

void	merge_quotes(char **commands, int i)
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
	while (commands[j] && !ft_strchr(commands[j], '"'))
	{
		merged = ft_strjoin(ft_strjoin(merged, " "),
				commands[j] + (commands[j][1] == '"'));
		free(commands[j++]);
	}
	if (commands[j])
	{
		*ft_strchr(commands[j], '"') = '\0';
		merged = ft_strjoin(ft_strjoin(merged, " "), commands[j]);
		free(commands[j++]);
	}
	commands[i] = merged;
	shift_command_left(commands, i, j);
}
