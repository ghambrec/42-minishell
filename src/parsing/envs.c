/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:31:02 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/10 16:33:58 by rstumpf          ###   ########.fr       */
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

char	*replace_env_vars(char *input)
{
	int				i;
	int				env_key_end;
	int				superrechnung;
	char			*output;
	char			*env_value;
	char			*env_key;
	t_quote_state	state;

	if (!ft_strchr(input, '$'))
		return (input);
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
	env_key_end = i;
	while ((ft_isalnum(input[env_key_end]) || ft_strchr("$_", input[env_key_end])) && input[env_key_end])
		env_key_end++;
	env_key = ft_substr(input, i + 1, env_key_end - i - 1);

	env_value = getenv(env_key);
	free(env_key);
	superrechnung = ft_strlen(input) - (env_key_end - i) + ft_strlen(env_value);
	output = (char *)malloc(superrechnung * sizeof(char));
	ft_strlcpy(output, input, i + 1);
	ft_strlcat(output, env_value, superrechnung);
	ft_strlcat(output, input + env_key_end, superrechnung);
	free(input);
	return(replace_env_vars(output));
}
