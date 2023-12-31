/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:39:18 by orudek            #+#    #+#             */
/*   Updated: 2023/09/12 16:36:29 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"
#include "error.h"
#include "free.h"
#include "split_args.h"

static char	ft_check_access(char *path, t_pipex *pipex)
{
	if (access(path, F_OK) == 0)
	{
		pipex->command.path = path;
		return (1);
	}
	return (0);
}

static char	ft_check_first_cmd(t_pipex *pipex)
{
	if (pipex->command.cmd == NULL)
		ft_return_msg(SPLIT_ERROR, 1, pipex);
	if (*pipex->command.cmd
		&& (!ft_strncmp(pipex->command.cmd[0], "./", 2)
			|| !ft_strncmp(pipex->command.cmd[0], "../", 3)
			|| pipex->command.cmd[0][0] == '/'))
	{
		if (ft_check_access(pipex->command.cmd[0], pipex))
			return (1);
		ft_return_perror(pipex->command.cmd[0], 0, pipex);
	}
	return (0);
}

static void	ft_get_command(char *str, char **path_list, t_pipex *pipex)
{
	char	*path;
	char	*aux;

	path = NULL;
	pipex->command.cmd = split_args(str, ' ');
	if (ft_check_first_cmd(pipex))
		return ;
	while (*pipex->command.cmd && path_list && *path_list != NULL)
	{
		aux = ft_strjoin("/", pipex->command.cmd[0]);
		path = ft_strjoin(*path_list, aux);
		ft_free(&aux);
		if (ft_check_access(path, pipex))
			return ;
		ft_free(&path);
		path = NULL;
		path_list++;
	}
	if (*pipex->command.cmd)
		write(2, pipex->command.cmd[0], ft_strlen(pipex->command.cmd[0]));
	else
		write(2, "\"\"", 2);
	ft_return_msg(CMD_ERROR, 127, pipex);
}

void	ft_child1(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		ft_return_perror(argv[1], 1, pipex);
	ft_get_command(argv[2], pipex->path, pipex);
	if (dup2(pipex->infile, 0) == -1)
		ft_return_perror(DUP2, 1, pipex);
	close(pipex->infile);
	close(pipex->pipe[0]);
	if (dup2(pipex->pipe[1], 1) == -1)
		ft_return_perror(DUP2, 1, pipex);
	execve(pipex->command.path, pipex->command.cmd, envp);
	perror(pipex->command.cmd[0]);
	exit(1);
}

void	ft_child2(t_pipex *pipex, char **argv, char **envp)
{
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (pipex->outfile == -1)
		ft_return_perror(argv[4], 1, pipex);
	ft_get_command(argv[3], pipex->path, pipex);
	if (dup2(pipex->outfile, 1) == -1)
		ft_return_perror(DUP2, 1, pipex);
	close(pipex->outfile);
	close(pipex->pipe[1]);
	if (dup2(pipex->pipe[0], 0) == -1)
		ft_return_perror(DUP2, 1, pipex);
	execve(pipex->command.path, pipex->command.cmd, envp);
	perror(pipex->command.cmd[0]);
	exit(1);
}
