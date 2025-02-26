/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:40:29 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 09:52:39 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	        *input;
	t_token_type    *tokens = NULL;

	while (1)
	{
		input = readline("\033[0;36m> \033[0m");
		if (!input) // STRG-D closes the shell
			break ;
		
		// doing stuff
		// ...

		create_command_list(input, &tokens);

		free(input);
	}
	return (EXIT_SUCCESS);
}