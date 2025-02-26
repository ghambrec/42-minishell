/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:21:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 16:16:25 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	split_tokens_set_type(char **all_tokens, t_tokens **token_list)
{
	int		i;

	i = 0;
	while (all_tokens[i])
	{
		if (is_command(all_tokens[i]))
		{
			handle_commands(all_tokens, token_list, i);
			while (all_tokens[i] && is_operator(all_tokens[i][0]) == false
				&& is_redirector(all_tokens[i]) == false)
				i++;
		}
		else if (is_redirector(all_tokens[i]))
		{
			handle_redirects(all_tokens, token_list, i);
			i += 2;
		}
		else if (is_operator(all_tokens[i][0]))
		{
			handle_operator(all_tokens, token_list, i);
			i++;
		}
	}
}

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
	int		i;
	int		j;

	i = 0;
	j = 0;
	extra_spaces = count_extra_spaces(input);
	updatet_input = (char *)malloc(ft_strlen(input) + extra_spaces + 1);
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
			{
				updatet_input[j] = ' ';
				j++;
			}
		}
		else
		{
			updatet_input[j] = input[i];
			j++;
		}
		i++;
	}
	updatet_input[j] = '\0';
	return (updatet_input);
}

char	*change_input_string(char *input)
{
	char	*updatet_input;

	updatet_input = insert_spaces(input);
	return (updatet_input);
}

void	create_command_list(char *input, t_tokens **token_list)
{
	char	*updatet_input;

	updatet_input = change_input_string(input);
	split_tokens_set_type(ft_split(updatet_input, ' '), token_list);
	handle_quotes_and_envs(*token_list);
	ft_printlist(*token_list);
}

