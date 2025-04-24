/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nontty_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:14 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:31:17 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_nontty_input(void)
{
	char	*input;
	char	*new_line;

	new_line = get_next_line(STDIN_FILENO);
	while (new_line)
	{
		input = ft_strtrim(new_line, "\n");
		free(new_line);
		if (ft_strlen(input) == 0 || ft_str_only_whitespaces(input))
			free(input);
		else
			handle_input(input);
		new_line = get_next_line(STDIN_FILENO);
	}
}
