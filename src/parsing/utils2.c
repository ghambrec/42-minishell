/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:03:16 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 14:46:52 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_in_quotes(char *input, int i)
{
	bool			in_quotes;

	in_quotes = false;
	if (input[i] == '"' || input[i] == 39)
	{
		in_quotes = !in_quotes;
		if (in_quotes == true)
			printf("opened\n");
		else
			printf("clodes\n");
	}
	return (in_quotes);
}

void	replace_char(char *str, char old_char, char new_char)
{
	while (*str)
	{
		if (*str == old_char)
			*str = new_char;
		str++;
	}
}
