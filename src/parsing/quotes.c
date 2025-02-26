/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:01 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 14:14:40 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_quotes_and_envs(t_tokens *token_list)
{
	int	i;

	while (token_list)
	{
		i = 0;
		while (token_list->token[i])
		{
			if (token_list->token && token_list->token[i][0] == '"')
				handle_doule_quotes(token_list->token, i);
			i++;
		}
		token_list = token_list->next;
	}
}


char	*get_quote_string(char **command, int i)
{
	char	*quote_string;

	quote_string = ft_strdup("");
	while (command[i])
	{
		quote_string = ft_strjoin(quote_string, command[i]);
		quote_string = ft_strjoin(quote_string, " ");
		if (command[i][ft_strlen(command[i])] == '"')
			break ;
		i++;
	}
	return (quote_string);
}

void	handle_doule_quotes(char **command, int i)
{
	char	*quote_string;

	quote_string = get_quote_string(command, i);
	quote_string = remove_char(quote_string, '"');
	printf("Quote String: %s\n", quote_string);
}

char	*remove_char(char *string, char c)
{
	char	*final_string;
	int		i;
	int		j;

	j = c_count(string, c);
	final_string = (char *)malloc(ft_strlen(string) - j + 1);
	i = 0;
	j = 0;
	while (string[i])
	{
		if (string[i] != c)
		{
			final_string[j] = string[i];
			j++;
		}
		i++;
	}
	final_string[j] = '\0';
	return (final_string);
}

int	c_count(char *string, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[i])
	{
		if (string[i] == c)
			j++;
		i++;
	}
	return (j);
}
