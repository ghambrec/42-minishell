/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:46:29 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/18 19:28:27 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	// t_tokens tokens;

	while (1)
	{
		input = readline("\033[0;36m> \033[0m");
		if (!input) // STRG-D closes the shell
			break ;
		
		// doing stuff
		// ...

		printf("--> %s\n", input);

		
		add_history(input);
		free(input);
	}
	clear_history();
	return (EXIT_SUCCESS);
}
