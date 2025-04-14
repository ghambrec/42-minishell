/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:08:14 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/12 17:55:03 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print2d(char **array2d)
{
	while (*array2d)
	{
		printf("%s ", *array2d);
		array2d++;
	}
	printf("\n");
}

void	ft_print2d_gha(char **array2d)
{
	int	i;

	i = 0;
	while (*array2d)
	{
		printf("%i: [%s]\n", i, *array2d);
		array2d++;
		i++;
	}
}

void	ft_printlist(t_tokens *token)
{
	while (token)
	{
		printf("Token Type: %d ", token->token_type);
		ft_print2d(token->token);
		token = token->next;
	}
}

int	get_token_type(char **token)
{
	int	token_type;

	if (token[0][0] == '|' && token[0][1] == '|')
		token_type = TT_OR;
	else if (token[0][0] == '|')
		token_type = TT_PIPE;
	else if (token[0][0] == '>' && token[0][1] == '>')
		token_type = TT_RE_APPEND;
	else if (token[0][0] == '<' && token[0][1] == '<')
		token_type = TT_HEREDOC;
	else if (token[0][0] == '&' && token[0][1] == '&')
		token_type = TT_AND;
	else if (token[0][0] == '(')
		token_type = TT_PARENTESIS_OPEN;
	else if (token[0][0] == ')')
		token_type = TT_PARENTESIS_CLOSE;
	else if (token[0][0] == '<')
		token_type = TT_RE_INPUT;
	else
		token_type = TT_RE_OUTPUT;
	return (token_type);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

void replace_char(char *str, char old_char, char new_char)
{
    while (*str) {
        if (*str == old_char) {
            *str = new_char;
        }
        str++;
    }
}