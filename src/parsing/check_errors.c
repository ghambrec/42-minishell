/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:43:18 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/27 13:36:31 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	no_open_quotes(char *input)
{
	int		i;
	char	quote_type;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == 39)
		{
			quote_type = input[i];
			i++;
			while (input[i] && input[i] != quote_type)
				i++;
			if (input[i] == '\0')
				return (ft_putendl_fd("No closing Quote", 2), true);
		}
		i++;
	}
	return (false);
}

bool	parsing_errors(char *input)
{
	if (no_open_quotes(input))
		return (true);
	return (false);
}
