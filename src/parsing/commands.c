/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:55 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/10 14:13:57 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_commands(char **all_tokens, t_tokens **token_list, int i)
{
	char	**commands;

	commands = get_commands(&all_tokens[i]);
	if (!commands)
		return ;
	ft_lstadd_back_token(token_list,
		ft_newtoken(TT_CMD, commands));
	return ;
}

char	**get_commands(char **tokens)
{
	char	**commands;
	int		i;
	int		j;

	i = 0;
	if (!tokens[i])
		return (NULL);
	while (tokens[i] && is_operator(tokens[i][0]) == false
		&& is_redirector(tokens[i]) == false)
		i++;
	commands = (char **)ft_calloc((i + 1), sizeof(char *));
	if (commands == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		commands[j] = tokens[j];
		j++;
	}
	commands[i] = NULL;
	return (commands);
}
