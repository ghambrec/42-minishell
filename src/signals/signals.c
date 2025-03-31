/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:22:40 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/31 16:23:23 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	set_signal_handler(int sigint, void (*handler)(int))
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	if (sigaction(sigint, &sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		exit(EXIT_FAILURE);
// 	}
// }
