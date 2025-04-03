/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/02 19:34:03 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*change_input_string(char *input)
{
	char	*updatet_input;

	updatet_input = insert_spaces(input);
	return (updatet_input);
}

static int	create_token_list(char **all_tokens, t_tokens **token_list)
{
	int		i;

	i = 0;
	while (all_tokens[i])
	{
		if (is_command(all_tokens[i]))
			handle_commands(all_tokens, token_list, &i);
		else if (all_tokens[i + 1]
			&& is_heredoc_or_append(all_tokens[i][0], all_tokens[i + 1][0]))
			handle_heredoc_and_append(all_tokens, token_list, &i);
		else if (all_tokens[i + 1]
			&& is_operator(all_tokens[i][0]))
			handle_operator(all_tokens, token_list, &i);
		else if (all_tokens[i + 1]
			&& is_redirector(all_tokens[i]))
			handle_redirects(all_tokens, token_list, &i);
		else if (!all_tokens[i + 1])
			return (ft_putendl_fd("parse error near `newline'", 2), -1);
		else
			i++;
	}
	return (0);
}

int	create_command_list(char *input, t_tokens **token_list)
{
	char		*updated_input;
	char		**splitted_tokens;

	updated_input = change_input_string(input);
	free(input);
	splitted_tokens = split_into_tokens(updated_input);
	free(updated_input);
	if (create_token_list(splitted_tokens, token_list) == -1)
		return (free_split(splitted_tokens), -1);
	free_split(splitted_tokens);
	handle_quotes(token_list);
	join_commands(*token_list);
	return (1);
}
