/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:52:32 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/19 10:53:46 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_split(char **split)
{
	char	**orig;

	orig = split;
	while (*split != NULL)
	{
		free(*split);
		split++;
	}
	free(orig);
}
