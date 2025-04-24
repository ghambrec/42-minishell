/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:18 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:43:59 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(char *input)
{
	t_tokens	*tokens;
	t_ast		*ast;

	tokens = NULL;
	if (parsing_errors(input))
	{
		get_shell()->exit_code = 2;
		return ;
	}
	if (create_command_list(input, &tokens) == EXIT_FAILURE)
	{
		get_shell()->exit_code = 2;
		return ;
	}
	ast = ast_create_tree(&tokens);
	get_shell()->ast = ast;
	free_tokens(tokens);
	tokens = NULL;
	exec_ast(ast);
	free_ast(ast);
}
