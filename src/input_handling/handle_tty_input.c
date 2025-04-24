/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tty_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:08 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:31:11 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tty_input(void)
{
	char	*input;

	while (true)
	{
		input = NULL;
		if (get_shell()->exit_code)
			input = readline("\033[0;31m• \033[0;36m➜\033[0m ");
		else
			input = readline("\033[0;32m• \033[0;36m➜\033[0m ");
		if (!input)
		{
			ft_putendl_fd("\033[A\033[2K\033[0;30m• \033[0;36m➜\033[0m exit",
				STDOUT_FILENO);
			break ;
		}
		if (ft_strlen(input) == 0 || ft_str_only_whitespaces(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		handle_input(input);
	}
}
