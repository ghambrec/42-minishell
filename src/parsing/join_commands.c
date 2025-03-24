/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:49:17 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/13 19:11:53 by rstumpf          ###   ########.fr       */
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

static void	join_commands_to_one_token(t_tokens *tokens, char **commands)
{
	bool		first_command;
	t_tokens	*temp;

	first_command = true;
	while (tokens)
	{
		if (tokens->token_type == TT_CMD && first_command == true)
		{
			temp = tokens;
			first_command = false;
		}
		tokens = tokens->next;
	}
	free_split(temp->token);
	temp->token = commands;
}

static void	remove_joined_tokens(t_tokens *tokens)
{
	t_tokens	*last_token;
	t_tokens	*temp;
	bool		first_command;

	first_command = true;
	last_token = NULL;
	while (tokens)
	{
		if (tokens->token_type == TT_CMD)
		{
			if (first_command)
			{
				first_command = false;
				last_token = tokens;
				tokens = tokens->next;
				continue ;
			}
			free_split(tokens->token);
			if (last_token)
				last_token->next = tokens->next;
			temp = tokens;
			tokens = tokens->next;
			free(temp);
			continue ;
		}
		last_token = tokens;
		tokens = tokens->next;
	}
}

void	join_commands(t_tokens *tokens)
{
	char	**commands;
	int		to_allocate;

	to_allocate = get_number_of_commands(tokens);
	commands = duplicate_commands(tokens, to_allocate);
	join_commands_to_one_token(tokens, commands);
	remove_joined_tokens(tokens);
}
