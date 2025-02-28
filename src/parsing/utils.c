/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:08:14 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/28 16:35:14 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print2d(char **array2d)
{
	while (*array2d)
	{
		printf("%s ", *array2d);
		array2d++;
	}
	printf("\n");
}

void	ft_printlist(t_tokens *token)
{
	while (token)
	{
		printf("Token Type: %d ", token->token_type);
		ft_print2d(token->token);
		token = token->next;
	}
}

int	get_token_type(char **token)
{
	int	token_type;

	if (token[0][0] == '|' && token[0][1] == '|')
		token_type = TT_OR;
	else if (token[0][0] == '|')
		token_type = TT_PIPE;
	else if (token[0][0] == '>' && token[0][1] == '>')
		token_type = TT_RE_APPEND;
	else if (token[0][0] == '<' && token[0][1] == '<')
		token_type = TT_HEREDOC;
	else if (token[0][0] == '&' && token[0][1] == '&')
		token_type = TT_AND;
	else if (token[0][0] == '(')
		token_type = TT_PARENTESIS_OPEN;
	else if (token[0][0] == ')')
		token_type = TT_PARENTESIS_CLOSE;
	else if (token[0][0] == '<')
		token_type = TT_RE_INPUT;
	else
		token_type = TT_RE_OUTPUT;
	return (token_type);
}
