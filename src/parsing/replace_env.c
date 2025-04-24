/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:38 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/24 17:10:14 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*extract_env_info(char *input, int i,
	int *env_key_end, char **env_val)
{
	char	*env_key;

	*env_key_end = i + 1;
	while ((ft_isalnum(input[*env_key_end]) || input[*env_key_end] == '_')
		&& input[*env_key_end])
		(*env_key_end)++;
	env_key = ft_substr(input, i + 1, *env_key_end - i - 1);
	*env_val = ft_getenv(env_key);
	free(env_key);
	return (*env_val);
}

char	*replace_env_var_in_string(char *input, int i)
{
	int		env_key_end;
	int		new_len;
	char	*env_val;
	char	*output;

	if (input[i + 1] && !ft_isalnum(input[i + 1]))
	{
		replace_char(input, '$', '\e');
		return (ft_strdup(input));
	}
	env_val = extract_env_info(input, i, &env_key_end, &env_val);
	if (env_val)
		new_len = ft_strlen(input) - (env_key_end - i) + ft_strlen(env_val) + 1;
	else
		new_len = ft_strlen(input) - (env_key_end - i) + 1;
	output = (char *)malloc(new_len * sizeof(char));
	if (!output)
		return (NULL);
	ft_strlcpy(output, input, i + 1);
	if (env_val)
		ft_strlcat(output, env_val, new_len);
	ft_strlcat(output, input + env_key_end, new_len);
	return (output);
}
