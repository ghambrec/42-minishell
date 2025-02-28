/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/28 23:50:20 by rstumpf          ###   ########.fr       */
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
		else if (is_heredoc_or_append(all_tokens[i][0], all_tokens[i + 1][0]))
		{
			handle_heredoc_and_append(all_tokens, token_list, i);
			i += 2;
		}
		else if (is_operator(all_tokens[i][0]))
		{
			handle_operator(all_tokens, token_list, i);
			i++;
		}
		else if (is_redirector(all_tokens[i]))
		{
			handle_redirects(all_tokens, token_list, i);
			i += 2;
		}
		else
			i++;
	}
	i = 0;
}

char	*change_input_string(char *input)
{
	char	*updatet_input;

	updatet_input = insert_spaces(input);
	replace_env_vars(input, updatet_input);
	printf("updated: %s\n", updatet_input);
	return (updatet_input);
}

void	create_command_list(char *input, t_tokens **token_list)
{
	char		*updatet_input;
	t_tokens	*temp;

	updatet_input = change_input_string(input);
	split_tokens_set_type(ft_split(updatet_input, ' '), token_list);
	temp = *token_list;
	while (*token_list)
	{
		handle_quotes((*token_list)->token);
		*token_list = (*token_list)->next;
	}
	ft_printlist(temp);
}
