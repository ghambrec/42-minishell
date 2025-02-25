/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:36:13 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/25 13:16:08 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_type	*ft_newtoken(int token_type, char **token)
{
	t_token_type	*new_entry;

	new_entry = (t_token_type *)malloc(sizeof(t_token_type));
	if (!new_entry)
	{
		return (NULL);
	}
	new_entry->token_type = token_type;
	new_entry->token = token;
	new_entry->next = NULL;
	return (new_entry);
}

void	ft_lstadd_back_token(t_token_type **lst, t_token_type *new)
{
	t_token_type	*last_entry;

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

t_token_type	*ft_lstlast_token(t_token_type *lst)
{
	t_token_type	*last_entry;

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
