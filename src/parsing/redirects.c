/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:13:18 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 14:12:33 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirects(char **all_tokens, t_tokens **token_list, int i)
{
	int				token_type;
	char			**token_args;
	t_tokens	*token_node;

	token_args = get_redirects_2d(&all_tokens[i]);
	token_type = get_token_type(token_args);
	token_node = ft_newtoken(token_type, token_args);
	ft_lstadd_back_token(token_list, token_node);
	return (0);
}

char	**get_redirects_2d(char **all_tokens)
{
	char	**commands;
	int		i;

	i = 0;
	while (all_tokens[i][0] != '>' && all_tokens[i][0] != '<')
		i++;
	commands = (char **)malloc((3) * sizeof(char *));
	if (commands == NULL)
		return (NULL);
	commands[0] = all_tokens[i];
	commands[1] = all_tokens[i + 1];
	commands[2] = NULL;
	return (commands);
}
