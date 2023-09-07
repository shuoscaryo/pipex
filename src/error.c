/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:07:03 by orudek            #+#    #+#             */
/*   Updated: 2023/09/07 13:39:51 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdio.h>
#include "libft.h"
#include "free.h"

void	ft_return_msg(const char *msg, int error_code, t_pipex *pipex)
{
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	ft_free_pipex(pipex);
	exit(error_code);
}

void	ft_return_perror(const char *msg, int error_code, t_pipex *pipex)
{	
	perror(msg);
	ft_free_pipex(pipex);
	exit(error_code);
}
