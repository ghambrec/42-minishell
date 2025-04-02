/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstumpf <rstumpf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:46:25 by rstumpf           #+#    #+#             */
/*   Updated: 2025/04/02 18:46:56 by rstumpf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_writer(int fd, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, eof) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}

int	redirect_heredoc(t_redirection *eof)
{
	int	fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		return (errno);
	}
	heredoc_writer(fd, eof->filename);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("heredoc RD");
		return (errno);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

