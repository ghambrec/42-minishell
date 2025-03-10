/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:32:42 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/10 10:23:54 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_operator(char c)
{
	if (c && (c == '|'))
		return (true);
	return (false);
}

bool	need_space(char c)
{
	if (c && (c == '|' || c == '<' || c == '>'))
		return (true);
	return (false);
}

bool	is_redirector(char *c)
{
	if (!c)
		return (false);
	else if ((c[0] == '<' && c[1] != '<') || (c[0] == '>' && c[1] != '>'))
		return (true);
	return (false);
}

bool	is_command(char *check)
{
	if (check && is_operator(check[0]) == false
		&& is_redirector(check) == false)
		return (true);
	return (false);
}

bool	is_heredoc_or_append(char c, char d)
{
	if (!c)
		return (false);
	else if ((c == '<' && d == '<') || (c == '>' && d == '>'))
		return (true);
	return (false);
}
