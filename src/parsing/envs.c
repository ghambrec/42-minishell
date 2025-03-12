/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:31:02 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/12 12:53:07 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_quotes(char c, t_quote_state *state)
{
	if (c == '"' && !state->in_single_quotes)
	{
		state->in_double_quotes = !state->in_double_quotes;
	}
	else if (c == 39 && !state->in_double_quotes)
	{
		state->in_single_quotes = !state->in_single_quotes;
	}
}

static bool	all_vars_replaced(char *input)
{
	int				i;
	t_quote_state	state;

	state.in_single_quotes = false;
	state.in_double_quotes = false;
	i = 0;
	if (!ft_strchr(input, '$'))
		return (true);
	while (input[i])
	{
		check_quotes(input[i], &state);
		if (input[i] == '$' && !state.in_single_quotes)
			return (false);
		i++;
	}
	return (true);
}

static char	*replace_env_var_in_string(char *input, int i)
{
	int		env_key_end;
	int		new_len;
	char	*env_key;
	char	*env_value;
	char	*output;

	env_key_end = i;
	while ((ft_isalnum(input[env_key_end])
			|| ft_strchr("$_", input[env_key_end])) && input[env_key_end])
		env_key_end++;
	env_key = ft_substr(input, i + 1, env_key_end - i - 1);
	env_value = getenv(env_key);
	free(env_key);
	new_len = ft_strlen(input) - (env_key_end - i) + ft_strlen(env_value) + 1;
	output = (char *)malloc(new_len * sizeof(char));
	ft_strlcpy(output, input, i + 1);
	ft_strlcat(output, env_value, new_len);
	ft_strlcat(output, input + env_key_end, new_len);
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
	state.in_single_quotes = false;
	state.in_double_quotes = false;
	while (input[i])
	{
		check_quotes(input[i], &state);
		if (input[i] == '$' && !state.in_single_quotes)
			break ;
		i++;
	}
	output = replace_env_var_in_string(input, i);
	free(input);
	return (replace_env_vars(output));
}
