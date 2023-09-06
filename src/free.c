/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:33:00 by orudek            #+#    #+#             */
/*   Updated: 2023/09/06 17:08:43 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	ft_pipex_init(t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;
	pipex->path = NULL;
	pipex->command.path = NULL;
	pipex->command.cmd = NULL;
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd->path)
		ft_free(&cmd->path);
	if (cmd->cmd)
		ft_free_array(&cmd->cmd);
}

char	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipe[0] != -1)
		close(pipex->pipe[0]);
	if (pipex->pipe[1] != -1)
		close(pipex->pipe[1]);
	ft_free_array(&pipex->path);
	ft_free_cmd(&pipex->command);
	ft_pipex_init(pipex);
	return (0);
}

void	ft_free_array(char ***array)
{
	int	i;

	i = 0;
	if ((*array) == NULL)
		return ;
	while ((*array)[i] != NULL)
		free((*array)[i++]);
	free((*array));
	(*array) = NULL;
}
