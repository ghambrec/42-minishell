/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:04:01 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 17:24:29 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_extra_spaces(char *input)
{
	int	i;
	int	spaces_needed;

	i = 0;
	spaces_needed = 0;
	while (input[i])
	{
		if (need_space(input[i]))
		{
			if (input[i - 1] != ' ')
				spaces_needed++;
			if (input[i + 1] != ' ')
				spaces_needed++;
		}
		i++;
	}
	return (spaces_needed);
}

char	*insert_spaces(char *input)
{
	char	*updatet_input;
	int		extra_spaces;

	extra_spaces = count_extra_spaces(input);
	updatet_input = (char *)malloc(ft_strlen(input) + extra_spaces + 1);
	copy_with_spaces(input, updatet_input);
	return (updatet_input);
}

void	copy_with_spaces(char *input, char *updatet_input)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (need_space(input[i]))
		{
			if (updatet_input[j - 1] != ' ')
			{
				updatet_input[j] = ' ';
				j++;
			}
			updatet_input[j] = input[i];
			j++;
			if (input[i + 1] != ' ')
				updatet_input[j++] = ' ';
		}
		else
			updatet_input[j++] = input[i];
		i++;
	}
	updatet_input[j] = '\0';
}
