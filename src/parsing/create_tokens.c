/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/24 18:21:52 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_token_list(char **all_tokens, t_tokens **token_list)
{
	int		i;

	i = 0;
	while (all_tokens[i])
	{
		if (is_command(all_tokens[i]))
		{
			handle_commands(all_tokens, token_list, &i);
		}
		else if (is_heredoc_or_append(all_tokens[i][0], all_tokens[i + 1][0]))
			handle_heredoc_and_append(all_tokens, token_list, &i);
		else if (is_operator(all_tokens[i][0]))
			handle_operator(all_tokens, token_list, &i);
		else if (is_redirector(all_tokens[i]))
			handle_redirects(all_tokens, token_list, &i);
		else
			i++;
	}
	i = 0;
}

char	*change_input_string(char *input)
{
	char	*updatet_input;

	updatet_input = insert_spaces(input);
	return (updatet_input);
}

void	create_command_list(char *input, t_tokens **token_list)
{
	char		*updated_input;
	char		**splitted_tokens;

	updated_input = change_input_string(input);
	free(input);
	splitted_tokens = split_into_tokens(updated_input);
	free(updated_input);
	create_token_list(splitted_tokens, token_list);
	free_split(splitted_tokens);
	handle_quotes(token_list);
	join_commands(*token_list);
}
