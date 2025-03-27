/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:34:34 by rstumpf           #+#    #+#             */
/*   Updated: 2025/03/27 16:30:40 by ghambrec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	free_pointers(char *path, char *slashed_path, char *new_path)
{
	free(path);
	free(slashed_path);
	free(new_path);
}

static int	cd_dir(char **cmd)
{
	if (chdir(cmd[1]) == -1)
	{
		perror("cd");
		return (errno);
	}
	return (EXIT_SUCCESS);
}

static int	cd_home(char *path)
{
	path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("cd");
		return (free(path), errno);
	}
	return (EXIT_SUCCESS);
}

static int	cd_path(char *path, char *slashed_path, char *new_path, char **cmd)
{
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("cd, error get pwd");
		return (errno);
	}
	slashed_path = ft_strjoin(path, "/");
	new_path = ft_strjoin(slashed_path, cmd[1]);
	if (chdir(new_path) == -1)
	{
		perror("cd");
		return (errno);
	}
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **cmd)
{
	char	*path;
	char	*slashed_path;
	char	*new_path;
	int		err_code;

	path = NULL;
	slashed_path = NULL;
	new_path = NULL;
	if (!cmd[1])
		err_code = cd_home(path);
	else if (cmd[1][0] == '/')
		err_code = cd_dir(cmd);
	else
		err_code = cd_path(path, slashed_path, new_path, cmd);
	free_pointers(path, slashed_path, new_path);
	return (err_code);
}
