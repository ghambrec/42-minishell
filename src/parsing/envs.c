/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:31:02 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 18:27:50 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char c, t_quote_state *state)
{
	if (c == '"' && !state->sq)
	{
		state->dq = !state->dq;
	}
	else if (c == 39 && !state->dq)
	{
		state->sq = !state->sq;
	}
}

static bool	all_vars_replaced(char *input)
{
	int				i;
	t_quote_state	state;

	state.sq = false;
	state.dq = false;
	i = 0;
	if (!ft_strchr(input, '$'))
		return (true);
	while (input[i])
	{
		check_quotes(input[i], &state);
		if (input[i] == '$' && !state.sq)
			return (false);
		i++;
	}
	return (true);
}

static char	*replace_exit_code(char *input, int i)
{
	char	*output;
	int		new_len;
	char	*exit_code_str;

	exit_code_str = ft_itoa(get_shell()->exit_code);
	new_len = ft_strlen(input) - 2 + ft_strlen(exit_code_str) + 1;
	output = (char *)malloc(new_len);
	ft_strlcpy(output, input, i + 1);
	ft_strlcat(output, exit_code_str, new_len);
	ft_strlcat(output, &input[i + 2], new_len);
	free(exit_code_str);
	return (output);
}

char	*replace_env_vars(char *input)
{
	int				i;
	t_quote_state	state;
	char			*output;

	if (all_vars_replaced(input))
		return (input);
	output = NULL;
	i = 0;
	state.sq = false;
	state.dq = false;
	while (input[i])
	{
		check_quotes(input[i], &state);
		if (input[i] == '$' && !state.sq)
			break ;
		i++;
	}
	if (input[i] && input[i + 1] == '?')
	{
		output = replace_exit_code(input, i);
		return (free(input), replace_env_vars(output));
	}
	output = replace_env_var_in_string(input, i);
	free(input);
	return (replace_env_vars(output));
}
