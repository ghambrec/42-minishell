/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:08:14 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/20 11:08:17 by rstumpf          ###   ########.fr       */
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
		token_type = OR;
	else if (token[0][0] == '|')
		token_type = PIPE;
	else if (token[0][0] == '<' && token[0][1] == '<')
		token_type = HEREDOC;
	else if (token[0][0] == '>')
		token_type = RE_OUTPUT;
	else if (token[0][0] == '&' && token[0][1] == '&')
		token_type = AND;
	else if (token[0][0] == '<')
		token_type = RE_INPUT;
	else if (token[0][0] == '>' && token[0][1] == '>')
		token_type = RE_APPEND;
	else
		token_type = RE_OUTPUT;
	return (token_type);
}
