/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 14:12:14 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	split_tokens_set_type(char **all_tokens, t_tokens **token_list)
{
	int		i;

	i = 0;
	while (all_tokens[i])
	{
		if (is_command(all_tokens[i]))
		{
			handle_commands(all_tokens, token_list, i);
			while (all_tokens[i] && is_operator(all_tokens[i][0]) == false
				&& is_redirector(all_tokens[i]) == false)
				i++;
		}
		else if (is_redirector(all_tokens[i]))
		{
			handle_redirects(all_tokens, token_list, i);
			i += 2;
		}
		else if (is_operator(all_tokens[i][0]))
		{
			handle_operator(all_tokens, token_list, i);
			i++;
		}
	}
}

void	create_command_list(char *input, t_tokens **token_list)
{
	split_tokens_set_type(ft_split(input, ' '), token_list);
	handle_quotes_and_envs(*token_list);
	ft_printlist(*token_list);
}

