/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:07:17 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/25 13:27:58 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	t_token_type	*token_list;
	char			*input;

	token_list = NULL;
	input = "grep pattern hello < input.txt | wc -l > output.txt ( wc ) & hello";
	create_command_list(input, &token_list);
}
