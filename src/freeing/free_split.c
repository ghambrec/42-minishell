/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:27 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:31:30 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	char	**orig;

	if (!split)
		return ;
	orig = split;
	while (*split != NULL)
	{
		free(*split);
		*split = NULL;
		split++;
	}
	free(orig);
}
