/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:18 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:31:21 by rstumpf          ###   ########.fr       */
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
	free_tokens(tokens);
	tokens = NULL;
	exec_ast(ast);
	free_ast(ast);
}
