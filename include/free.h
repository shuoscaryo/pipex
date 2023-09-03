/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:34:32 by orudek            #+#    #+#             */
/*   Updated: 2023/08/15 20:13:15 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "pipex.h"

void	ft_pipex_init(t_pipex *pipex);
void	ft_free(char **str);
void	ft_free_cmd(t_cmd *cmd);
char	ft_free_pipex(t_pipex *pipex);
void	ft_free_array(char ***array);

#endif