/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:13 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/26 14:16:53 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens	*ft_newtoken(int token_type, char **token)
{
	t_tokens	*new_entry;

	new_entry = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_entry)
	{
		return (NULL);
	}
	new_entry->token_type = token_type;
	new_entry->token = token;
	new_entry->next = NULL;
	return (new_entry);
}

void	ft_lstadd_back_token(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last_entry;

	if (new == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_entry = ft_lstlast_token(*lst);
	last_entry->next = new;
}

t_tokens	*ft_lstlast_token(t_tokens *lst)
{
	t_tokens	*last_entry;

	if (lst == NULL)
	{
		return (NULL);
	}
	last_entry = lst;
	while (last_entry->next != NULL)
	{
		last_entry = last_entry->next;
	}
	return (last_entry);
}
