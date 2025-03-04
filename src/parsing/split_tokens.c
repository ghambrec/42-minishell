/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:05:38 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/04 13:47:41 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_space(char c)
{
	return (c == ' ');
}

static char	*copy_token(char *input, int start, int end)
{
	char	*token;

	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, input + start, end - start + 1);
	token[end - start] = '\0';
	return (token);
}

static void	skip_spaces(char *input, int *i)
{
	while (input[*i] && is_space(input[*i]) && !is_in_quotes(input, *i))
		(*i)++;
}

static void	inside_quotes(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
}

char	**split_tokens(char *input)
{
	int		i;
	int		start;
	int		token_count;
	char	**tokens;

	tokens = malloc(sizeof(char *) * (ft_strlen(input) / 2 + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	token_count = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (input[i] == '\0')
			break ;
		start = i;
		if (input[i] == '"' || input[i] == 39)
		{
			inside_quotes(input, &i, input[i]);
			while (input[i] && !is_space(input[i]))
				i++;
		}
		else
		{
			while (input[i] && (!is_space(input[i]) || is_in_quotes(input, i)))
				i++;
		}
		tokens[token_count] = copy_token(input, start, i);
		if (!tokens[token_count])
			return (NULL);
		token_count++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
