/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:31:01 by ghambrec          #+#    #+#             */
/*   Updated: 2025/02/19 11:11:03 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*get_path(char *programm)
{
	char	**paths;
	char	*half_path;
	char	*full_path;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		half_path = ft_strjoin(paths[i], "/");
		if (!half_path)
			return (free_split(paths), NULL);
		full_path = ft_strjoin(half_path, programm);
		free(half_path);
		if (!full_path)
			return (free_split(paths), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_split(paths), NULL);
}

void	execute_command(char **cmd)
{
	char	*path;

	path = get_path(cmd[0]);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd[0], STDERR_FILENO);
		free_split(cmd);
		return ;
	}
	if (execve(path, cmd, NULL) == -1)
	{
		ft_putstr_fd("Error executing command '", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		perror("'");
		free_split(cmd);
		// hier errno auf $? setzen?
		return ;
	}
}
