/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:07:03 by orudek            #+#    #+#             */
/*   Updated: 2023/09/06 20:58:22 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdio.h>
#include "libft.h"
#include "free.h"

void	ft_return_msg(const char *msg, int error_code)
{
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	exit(error_code);
}

void	ft_return_perror(const char *msg, int error_code)
{	
	perror(msg);
	exit(error_code);
}
