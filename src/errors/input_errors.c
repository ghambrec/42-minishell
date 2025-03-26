/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:06 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/26 19:56:56 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	input_errors(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
		return (ft_putendl_fd("no arguments for minishell allowed", 2), true);
	return (false);
}
