/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:39:55 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/19 11:12:04 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/myLibft/include/my_libft.h"
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

enum e_tokens
{
	CMD,
	PIPE,
	RE_INPUT,
	RE_OUTPUT,
	RE_APPEND,
	HEREDOC,
	AND,
	OR
};

typedef struct s_tokens
{
	int				id;
	enum e_tokens	token_type;
	char			**token;
	struct s_ctbl	*next;
} t_tokens;


// FREEING
void	free_split(char **split);

// EXECUTING
void	execute_command(char **cmd);

#endif