/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:06 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/25 15:54:54 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	input_errors(int argc, char **argv)
{
	argv = NULL;
	if (argc > 1)
		return (ft_putendl_fd("no arguments for minishell allowed", 2), true);
	return (false);
}
