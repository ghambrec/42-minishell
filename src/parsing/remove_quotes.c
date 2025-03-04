/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:54 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/04 19:40:54 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"\

static int	count_wihtout_quotes(char *command)
{
    int i = 0;
    int j = 0;
    char rm_quote = 0;
    bool in_quotes = false;

    while (command[i])
    {
        if ((command[i] == '"' || command[i] == 39))
        {
            if (!in_quotes)
            {
                // Start of outermost quotes
                rm_quote = command[i];
                in_quotes = true;
            }
            else if (command[i] == rm_quote)
            {
                // End of outermost quotes
                in_quotes = false;
            }
            else
            {
                // Nested quotes, count them
                j++;
            }
        }
        else
        {
            // Count non-quote characters
            j++;
        }
        i++;
    }
    return j;
}

char *remove_quotes(char *command)
{
    char rm_quote = 0;
    bool in_quotes = false;
    char *new_string;
    int j = 0;
    int k = 0;

    new_string = (char *)malloc(count_wihtout_quotes(command) + 1);
    if (!new_string)
        return NULL; // Handle malloc failure

    while (command[j])
    {
        if ((command[j] == '"' || command[j] == 39))
        {
            if (!in_quotes)
            {
                // Start of outermost quotes
                rm_quote = command[j];
                in_quotes = true;
            }
            else if (command[j] == rm_quote)
            {
                // End of outermost quotes
                in_quotes = false;
            }
            else
            {
                // Nested quotes, preserve them
                new_string[k++] = command[j];
            }
            j++;
        }
        else
        {
            // Copy non-quote characters
            new_string[k++] = command[j++];
        }
    }
    new_string[k] = '\0'; // Null-terminate the string
    return new_string;
}
