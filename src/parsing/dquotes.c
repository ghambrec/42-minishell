/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:01 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/07 14:06:02 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_quotes(t_tokens **token_list)
{
	char		**commands;
	int			i;
	t_tokens	*temp;

	temp = *token_list;
	while (*token_list)
	{
		commands = (*token_list)->token;
		i = 0;
		while (commands[i])
		{
			replace_env_vars(commands[i]);
			commands[i] = remove_quotes(commands[i]);
			i++;
		}
		*token_list = (*token_list)->next;
	}
	*token_list = temp;
	ft_printlist(temp);
}
