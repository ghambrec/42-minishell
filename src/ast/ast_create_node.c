/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:33:21 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:33:24 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_create_node(t_token_type ttype,
	char **cmd, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->ttype = ttype;
	new_node->cmd = cmd;
	new_node->redirect = NULL;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}
