/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:54 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/05 11:23:23 by rstumpf          ###   ########.fr       */
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

char	*remove_quotes(char *command)
{
	char	rm_quote;
	bool	in_quotes;
	char	*new_string;
	int		j;
	int		k;

	rm_quote = 0;
	in_quotes = false;
	j = 0;
	k = 0;
	new_string = (char *)malloc(count_wihtout_quotes(command) + 1);
	if (!new_string)
		return (NULL);
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
	return (new_string);
}
