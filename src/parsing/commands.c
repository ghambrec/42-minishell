/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:55 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/27 13:18:15 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**get_commands(char **tokens)
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
		commands[j] = ft_strdup(tokens[j]);
		j++;
	}
	commands[i] = NULL;
	return (commands);
}

void	handle_commands(char **all_tokens, t_tokens **token_list, int *i)
{
	char	**commands;

	commands = get_commands(&all_tokens[*i]);
	if (!commands)
		return ;
	ft_lstadd_back_token(token_list, ft_newtoken(TT_CMD, commands));
	while (all_tokens[*i] && is_operator(all_tokens[*i][0]) == false
		&& is_redirector(all_tokens[*i]) == false)
		(*i)++;
	return ;
}
