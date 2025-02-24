/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:04:58 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/20 11:06:27 by rstumpf          ###   ########.fr       */
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