/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:39:21 by orudek            #+#    #+#             */
/*   Updated: 2023/08/02 14:17:27 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILDREN_H
# define CHILDREN_H
# include "pipex.h"

void	ft_child1(t_pipex *pipex, char **argv, char **envp);
void	ft_child2(t_pipex *pipex, char **argv, char **envp);

#endif