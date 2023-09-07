/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:09:26 by orudek            #+#    #+#             */
/*   Updated: 2023/09/07 13:40:15 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "pipex.h"
# define ARG_ERROR "ERROR: Invalid number of arguments."
# define PATH_ERROR "ERROR: Couldn't get path."
# define SPLIT_ERROR "ERROR: Couldn't get command string."
# define CMD_ERROR ": command not found"
# define PIPE "Pipe"
# define DUP2 "Dup2"
# define EXCVE "EXCVE"

void	ft_return_msg(const char *msg, int error_code, t_pipex *pipex);
void	ft_return_perror(const char *msg, int error_code, t_pipex *pipex);

#endif