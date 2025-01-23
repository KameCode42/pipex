/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:59:34 by dle-fur           #+#    #+#             */
/*   Updated: 2025/01/23 11:00:00 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	if (pipex->input_fd != -1)
		close(pipex->input_fd);
	if (pipex->output_fd != -1)
		close(pipex->output_fd);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	free_c(pipex->cmd1);
	pipex->cmd1 = NULL;
	free_c(pipex->cmd2);
	pipex->cmd2 = NULL;
}

void	free_c(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
