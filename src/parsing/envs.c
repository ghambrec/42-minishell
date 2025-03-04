/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:31:02 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/04 09:16:48 by rstumpf          ###   ########.fr       */
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

static void	handle_env_var(char *temp, int *i, t_quote_state *state)
{
	char	env_var_name[256];
	char	*env_var_value;
	int		k;

	k = 0;
	(*i)++;
	while (temp[*i] != '\0' && (ft_isalnum(temp[*i]) || temp[*i] == '_'))
		env_var_name[k++] = temp[(*i)++];
	env_var_name[k] = '\0';
	env_var_value = getenv(env_var_name);
	if (env_var_value != NULL)
	{
		ft_strcpy(&state->output[state->j], env_var_value);
		state->j += ft_strlen(env_var_value);
	}
}

void	replace_env_vars(char *output)
{
	char			*temp;
	int				i;
	t_quote_state	state;

	temp = ft_strdup(output);
	if (!temp)
		return ;
	state.output = output;
	state.j = 0;
	state.in_single_quotes = false;
	state.in_double_quotes = false;
	i = 0;
	while (temp[i] != '\0')
	{
		check_quotes(temp[i], &state);
		if (temp[i] == '$' && !state.in_single_quotes)
			handle_env_var(temp, &i, &state);
		else
			state.output[state.j++] = temp[i++];
	}
	state.output[state.j] = '\0';
	free(temp);
}
