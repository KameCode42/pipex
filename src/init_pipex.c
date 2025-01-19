/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:09:26 by david             #+#    #+#             */
/*   Updated: 2025/01/18 18:40:24 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipex(t_pipex *pipex, char **argv)
{
	pipex->input_file = argv[1];
	pipex->output_file = argv[4];
	pipex->input_fd = -1;
	pipex->output_fd = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->pid_child = 0;
	pipex->pid_parent = 0;
	pipex->cmd1 = ft_split(argv[2], ' ');
	if (pipex->cmd1 == NULL)
	{
		free_pipex(pipex);
		return (-1);
	}
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (pipex->cmd2 == NULL)
	{
		free_pipex(pipex);
		return (-1);
	}
	return (0);
}
