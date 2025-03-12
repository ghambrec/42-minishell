/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:54 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/12 13:41:43 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	quote_counter(char c, bool *in_quotes,
		char *rm_quote, int *quote_count)
{
	if ((c == '"' || c == 39))
	{
		if (!*in_quotes)
		{
			*rm_quote = c;
			*(in_quotes) = true;
		}
		else if (c == *rm_quote)
			*(in_quotes) = false;
		else
			(*quote_count)++;
	}
	else
		(*quote_count)++;
}

static int	count_wihtout_quotes(char *command)
{
	int		i;
	int		quote_count;
	char	rm_quote;
	bool	in_quotes;

	i = 0;
	quote_count = 0;
	rm_quote = 0;
	in_quotes = false;
	while (command[i])
	{
		quote_counter(command[i], &in_quotes, &rm_quote, &quote_count);
		i++;
	}
	return (quote_count);
}

static void	copy_without_unnecessary_quoets(char *command, char *new_string,
			bool in_quotes, char rm_quote)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (command[j])
	{
		if ((command[j] == '"' || command[j] == 39))
		{
			if (!in_quotes)
			{
				rm_quote = command[j];
				in_quotes = true;
			}
			else if (command[j] == rm_quote)
				in_quotes = false;
			else
				new_string[k++] = command[j];
			j++;
		}
		else
			new_string[k++] = command[j++];
	}
	new_string[k] = '\0';
}

char	*remove_quotes(char *command)
{
	char	rm_quote;
	bool	in_quotes;
	char	*new_string;
	int		new_string_len;

	rm_quote = 0;
	in_quotes = false;
	new_string_len = count_wihtout_quotes(command) + 1;
	new_string = (char *)malloc(new_string_len);
	if (!new_string)
		return (NULL);
	copy_without_unnecessary_quoets(command, new_string, in_quotes, rm_quote);
	free(command);
	return (new_string);
}
