/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:31:45 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/27 13:34:39 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	size_t	len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
	{
		if (free_s1)
			free((char *)s1);
		if (free_s2)
			free((char *)s2);
		return (NULL);
	}
	ft_strlcpy(res, s1, len + 1);
	ft_strlcat(res, s2, len + 1);
	if (free_s1)
		free((char *)s1);
	if (free_s2)
		free((char *)s2);
	return (res);
}
