/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:07:17 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/20 11:07:33 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	t_tokens	*token_list = NULL;
	char		*input;
	input = "    grep pattern     < input.txt | wc -l > output.txt";
	create_command_list(input, &token_list);
}