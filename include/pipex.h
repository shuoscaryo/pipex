/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:16:10 by orudek            #+#    #+#             */
/*   Updated: 2023/08/02 19:58:59 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

typedef struct s_pid
{
	int	id;
	int	status;
}	t_pid;

typedef struct s_pipex
{
	int		pipe[2];
	t_pid	pid[2];
	int		infile;
	int		outfile;
	char	**path;
	t_cmd	command;
}	t_pipex;

#endif