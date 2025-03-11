/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:54 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/10 16:26:05 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"\

static int	count_wihtout_quotes(char *command)
{
	int		i;
	int		j;
	char	rm_quote;
	bool	in_quotes;

	i = 0;
	j = 0;
	rm_quote = 0;
	in_quotes = false;
	while (command[i])
	{
		if ((command[i] == '"' || command[i] == 39))
		{
			if (!in_quotes)
			{
				rm_quote = command[i];
				in_quotes = true;
			}
			else if (command[i] == rm_quote)
				in_quotes = false;
			else
				j++;
		}
		else
			j++;
		i++;
	}
	return (j);
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

	rm_quote = 0;
	in_quotes = false;
	new_string = (char *)malloc(count_wihtout_quotes(command) + 1);
	if (!new_string)
		return (NULL);
	copy_without_unnecessary_quoets(command, new_string, in_quotes, rm_quote);
	return (new_string);
}
