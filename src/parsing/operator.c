/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:04:58 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/04 19:56:27 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_operator(char **all_tokens, t_tokens **token_list, int i)
{
	int		token_type;
	char	**operator;

	operator = get_operator(all_tokens[i]);
	token_type = get_token_type(operator);
	ft_lstadd_back_token(token_list,
		ft_newtoken(token_type, operator));
	return ;
}

char	**get_operator(char *operator)
{
	char	**operator_return;

	operator_return = (char **)malloc(2 * sizeof(char *));
	operator_return[0] = operator;
	operator_return[1] = NULL;
	return (operator_return);
}

char	**get_heredoc_or_append(char *operator)
{
	char	**token_return;

	token_return = (char **)malloc(2 * sizeof(char *));
	if (!token_return)
		return (NULL);
	token_return[0] = ft_strdup(operator);
	token_return[1] = NULL;
	return (token_return);
}

char	*join_tokens(char *token1, char *token2)
{
	char	*joined_token;

	joined_token = (char *)malloc(ft_strlen(token1) + ft_strlen(token2) + 1);
	if (!joined_token)
		return (NULL);
	ft_strcpy(joined_token, token1);
	ft_strlcat(joined_token, token2, ft_strlen(joined_token));
	return (joined_token);
}

void	handle_heredoc_and_append(
	char **all_tokens, t_tokens **token_list, int i)
{
	int		token_type;
	char	**token;
	char	*joined_token;

	joined_token = join_tokens(all_tokens[i], all_tokens[i + 1]);
	token = get_heredoc_or_append(joined_token);
	token_type = get_token_type(token);
	ft_lstadd_back_token(token_list, ft_newtoken(token_type, token));
	free(joined_token);
}
