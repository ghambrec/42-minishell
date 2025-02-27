/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:01 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/27 12:36:08 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_doule_quotes(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '"')
			merge_quotes(tokens, i);
		i++;
	}
}

bool	handle_immediate_end_quote(char **tokens, int i, char *merged)
{
	char	*end_quote;

	end_quote = ft_strchr(merged, '"');
	if (end_quote)
	{
		*end_quote = '\0';
		free(tokens[i]);
		tokens[i] = merged;
		return (true);
	}
	return (false);
}

char	*merge_tokens(char **tokens, int *j_ptr, char *merged)
{
	int		j;
	char	*end;

	j = *j_ptr;
	while (tokens[j] && !ft_strchr(tokens[j], '"'))
	{
		merged = merge_token(merged, tokens[j]);
		free(tokens[j++]);
	}
	if (tokens[j])
	{
		end = ft_strchr(tokens[j], '"');
		*end = '\0';
		merged = merge_token(merged, tokens[j]);
		free(tokens[j++]);
	}
	*j_ptr = j;
	return (merged);
}

char	*merge_token(char *merged, char *token)
{
	char	*temp;

	temp = ft_strjoin(merged, " ");
	free(merged);
	merged = temp;
	temp = ft_strjoin(merged, token);
	free(merged);
	return (temp);
}

void	merge_quotes(char **tokens, int i)
{
	char	*merged;
	char	*start;
	int		j;
	char	*end_quote;
	int		k;

	start = tokens[i] + 1;
	merged = ft_strdup(start);
	j = i;
	end_quote = ft_strchr(merged, '"');
	if (handle_immediate_end_quote(tokens, i, merged))
		return ;
	free(tokens[i]);
	j = i + 1;
	merged = merge_tokens(tokens, &j, merged);
	k = i + 1;
	while (tokens[j])
		tokens[k++] = tokens[j++];
	tokens[k] = NULL;
}
