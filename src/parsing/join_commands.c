/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:49:17 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:10:20 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_number_of_commands(t_tokens *tokens)
{
	int		i;
	int		to_allocate;

	to_allocate = 0;
	while (tokens && tokens->token_type != TT_PIPE)
	{
		i = 0;
		if (tokens && tokens->token_type == TT_CMD)
		{
			while (tokens->token[i])
			{
				i++;
				to_allocate++;
			}
		}
		tokens = tokens->next;
	}
	return (to_allocate);
}

static char	**duplicate_commands(t_tokens *tokens, int to_allocate)
{
	char	**commands;
	int		i;
	int		j;

	commands = (char **)ft_calloc((to_allocate + 1), sizeof(char *));
	j = 0;
	while (tokens && tokens->token_type != TT_PIPE)
	{
		if (tokens->token_type == TT_CMD)
		{
			i = 0;
			while (tokens->token[i])
			{
				commands[j] = ft_strdup(tokens->token[i]);
				i++;
				j++;
			}
		}
		tokens = tokens->next;
	}
	commands[j] = NULL;
	return (commands);
}

static t_tokens	*find_first_cmd_token(t_tokens *tokens)
{
	while (tokens && tokens->token_type != TT_PIPE)
	{
		if (tokens->token_type == TT_CMD)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

static void	remove_joined_cmd_tokens(t_tokens *first_token)
{
	t_tokens	*current;
	t_tokens	*prev;

	current = first_token->next;
	prev = first_token;
	while (current && current->token_type != TT_PIPE)
	{
		if (current->token_type == TT_CMD)
		{
			prev->next = current->next;
			free_split(current->token);
			free(current);
			current = prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	join_commands(t_tokens *tokens)
{
	t_tokens	*first_cmd_token;
	char		**commands;
	int			to_allocate;

	while (tokens)
	{
		first_cmd_token = find_first_cmd_token(tokens);
		if (!first_cmd_token)
			break ;
		to_allocate = get_number_of_commands(first_cmd_token);
		commands = duplicate_commands(first_cmd_token, to_allocate);
		free_split(first_cmd_token->token);
		first_cmd_token->token = commands;
		remove_joined_cmd_tokens(first_cmd_token);
		while (tokens && tokens->token_type != TT_PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
}
