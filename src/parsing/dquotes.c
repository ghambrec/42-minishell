/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:01 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/27 13:35:42 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_double_quotes(char **tokens)
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

bool	handle_immediate_end(char **tokens, int i, char *merged)
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
	else
		return (false);
}

void	shift_tokens_left(char **tokens, int i, int j)
{
	int	k;

	k = i + 1;
	while (tokens[j])
		tokens[k++] = tokens[j++];
	tokens[k] = NULL;
}

void	merge_quotes(char **tokens, int i)
{
	char	*merged;
	char	*start;
	int		j;

	start = tokens[i] + 1;
	merged = ft_strdup(start);
	if (handle_immediate_end(tokens, i, merged))
		return ;
	free(tokens[i]);
	j = i + 1;
	while (tokens[j] && !ft_strchr(tokens[j], '"'))
	{
		merged = ft_strjoin(ft_strjoin(merged, " "), tokens[j]);
		free(tokens[j++]);
	}
	if (tokens[j])
	{
		*ft_strchr(tokens[j], '"') = '\0';
		merged = ft_strjoin(ft_strjoin(merged, " "), tokens[j]);
		free(tokens[j++]);
	}
	tokens[i] = merged;
	shift_tokens_left(tokens, i, j);
}
