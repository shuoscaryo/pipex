/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:09:57 by orudek            #+#    #+#             */
/*   Updated: 2023/09/06 20:03:23 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "free.h"
#include "children.h"
#include "error.h"

static char	ft_get_path(char **envp, t_pipex *pipex)
{
	char	**path;

	while (*envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
		{
			path = ft_split(*envp + 5, ':');
			if (path == NULL)
				return (0);
			pipex->path = path;
			return (1);
		}
		envp++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	ft_pipex_init(&pipex);
	if (argc != 5)
		ft_return_msg(ARG_ERROR, 1, &pipex);
	ft_get_path(envp, &pipex);
	if (pipe(pipex.pipe) == -1)
		ft_return_perror(PIPE, 1, &pipex);
	pipex.pid[0].id = fork();
	if (pipex.pid[0].id == 0)
		ft_child1(&pipex, argv, envp);
	pipex.pid[1].id = fork();
	if (pipex.pid[1].id == 0)
		ft_child2(&pipex, argv, envp);
	ft_free_pipex(&pipex);
	waitpid(pipex.pid[0].id, NULL, 0);
	waitpid(pipex.pid[1].id, &pipex.pid[1].status, 0);
	return ((pipex.pid[1].status & 0xff00) >> 8);
}
