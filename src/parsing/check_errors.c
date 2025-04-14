/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:43:18 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/02 19:33:46 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	no_open_quotes(char *input)
{
	int		i;
	char	quote_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == 39)
		{
			quote_type = input[i];
			i++;
			while (input[i] && input[i] != quote_type)
				i++;
			if (input[i] == '\0')
				return (ft_putendl_fd("No closing Quote", 2), true);
		}
		i++;
	}
	return (false);
}

bool	parsing_errors(char *input)
{
	if (no_open_quotes(input))
		return (free(input), true);
	return (false);
}

// int	check_for_parse_errors(t_tokens *token)
// {
// 	while (token)
// 	{
// 		if (token->token_type == TT_RE_INPUT
// 			|| token->token_type == TT_RE_OUTPUT)
// 		{
// 			if (!ft_isalnum(token->token[1][0]))
// 				return (ft_putendl_fd("Parse Error", 2), EXIT_FAILURE);
// 		}
// 		// else if (token->token_type == TT_PIPE)
// 		// {
// 		// 	if (!token->next || token->next->token_type == TT_PIPE)
// 		// 		return (ft_putendl_fd("Parse Error", 2), EXIT_FAILURE);
// 		// }
// 		token = token->next;
// 	}
// 	return (EXIT_SUCCESS);
// }
