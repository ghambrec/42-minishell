/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:31:02 by rstumpf           #+#    #+#             */
/*   Updated: 2025/02/28 23:55:12 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_env_vars(char *input, char *output)
{
	int		i;
	int		j;
	int		k;
	char	env_var_name[256];
	char	*env_var_value;
	bool	in_single_quotes;
	bool	in_double_quotes;
	bool	is_opening;

	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (input[i] != '\0')
	{
		if (input[i] == '"' && !in_single_quotes)
		{
			is_opening = !in_double_quotes;
			if (is_opening && j > 0 && output[j - 1] != ' ')
				output[j++] = ' ';
			output[j++] = input[i++];
			in_double_quotes = !in_double_quotes;
			if (!is_opening && (input[i] != ' ' && input[i] != '\0'))
				output[j++] = ' ';
		}
		else if (input[i] == 39 && !in_double_quotes)
		{
			is_opening = !in_single_quotes;
			if (is_opening && j > 0 && output[j - 1] != ' ')
				output[j++] = ' ';
			output[j++] = input[i++];
			in_single_quotes = !in_single_quotes;
			if (!is_opening && (input[i] != ' ' && input[i] != '\0'))
				output[j++] = ' ';
		}
		else if (input[i] == '$' && !in_single_quotes)
		{
			i++;
			k = 0;
			while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_'))
				env_var_name[k++] = input[i++];
			env_var_name[k] = '\0';
			env_var_value = getenv(env_var_name);
			if (env_var_value != NULL)
			{
				strcpy(&output[j], env_var_value);
				j += strlen(env_var_value);
			}
		}
		else
			output[j++] = input[i++];
	}
	output[j] = '\0';
}
