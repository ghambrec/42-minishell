/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:33:16 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:33:19 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_create_tree(t_tokens **tokens)
{
	t_ast		*tree;
	t_tokens	*backup;

	backup = *tokens;
	tree = ast_parse_logical_operator(tokens);
	*tokens = backup;
	return (tree);
}
