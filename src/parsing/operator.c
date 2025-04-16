/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:04:58 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/03 20:47:49 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**get_operator(char *operator)
{
	char	**operator_return;

	operator_return = (char **)malloc(2 * sizeof(char *));
	if (!operator_return)
		return (NULL);
	operator_return[0] = ft_strdup(operator);
	operator_return[1] = NULL;
	return (operator_return);
}

void	handle_operator(char **all_tokens, t_tokens **token_list, int *i)
{
	int		token_type;
	char	**operator;

	operator = get_operator(all_tokens[*i]);
	token_type = get_token_type(operator);
	ft_lstadd_back_token(token_list, ft_newtoken(token_type, operator));
	(*i)++;
	return ;
}

static char	*join_tokens(char *token1, char *token2)
{
	char	*joined_token;

	joined_token = (char *)malloc(ft_strlen(token1) + ft_strlen(token2) + 1);
	if (!joined_token)
		return (NULL);
	joined_token = ft_strjoin(token1, token2);
	return (joined_token);
}

static char	**get_heredoc_or_append(char **all_tokens, int *i)
{
	char	**token_return;

	if (!all_tokens[*i + 2] || all_tokens[*i + 2][0] == '<')
		return (ft_putendl_fd("parse error near `newline'", 2), NULL);
	token_return = (char **)malloc(3 * sizeof(char *));
	if (!token_return)
		return (NULL);
	token_return[0] = join_tokens(all_tokens[*i], all_tokens[*i + 1]);
	token_return[1] = ft_strdup(all_tokens[*i + 2]);
	token_return[2] = NULL;
	return (token_return);
}


int	handle_heredoc_and_append(
	char **all_tokens, t_tokens **token_list, int *i)
{
	int		token_type;
	char	**token;

	token = get_heredoc_or_append(all_tokens, i);
	if (token == NULL)
		return (EXIT_FAILURE);
	token_type = get_token_type(token);
	ft_lstadd_back_token(token_list, ft_newtoken(token_type, token));
	(*i) += 3;
	return (EXIT_SUCCESS);
}
