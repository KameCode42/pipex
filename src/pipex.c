/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:21:30 by dle-fur           #+#    #+#             */
/*   Updated: 2025/01/23 11:05:36 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_pipex *pipex, char **env)
{
	if (pipe(pipex->pipe_fd) == -1)
	{
		free_pipex(pipex);
		exit(1);
	}
	pipex->pid_child = fork();
	if (pipex->pid_child == -1)
	{
		free_pipex(pipex);
		exit(1);
	}
	else if (pipex->pid_child == 0)
	{
		close(pipex->pipe_fd[0]);
		if (dup2(pipex->input_fd, STDIN_FILENO) == -1
			|| dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			free_pipex(pipex);
			exit(1);
		}
		close(pipex->pipe_fd[1]);
		close(pipex->input_fd);
		execute_command(pipex, env);
	}
}

void	execute_parents(t_pipex *pipex, char **env)
{
	pipex->pid_parent = fork();
	if (pipex->pid_parent == -1)
	{
		free_pipex(pipex);
		exit(1);
	}
	else if (pipex->pid_parent == 0)
	{
		close(pipex->pipe_fd[1]);
		if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1
			|| dup2(pipex->output_fd, STDOUT_FILENO) == -1)
		{
			free_pipex(pipex);
			exit(1);
		}
		close(pipex->pipe_fd[0]);
		close(pipex->output_fd);
		execute_command(pipex, env);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pipex->pid_child, NULL, 0);
	waitpid(pipex->pid_parent, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (check_args(argc, argv))
		return (1);
	if (init_pipex(&pipex, argv))
	{
		free_pipex(&pipex);
		return (1);
	}
	if (check_files(&pipex))
	{
		free_pipex(&pipex);
		return (1);
	}
	execute_child(&pipex, env);
	execute_parents(&pipex, env);
	close(pipex.input_fd);
	close(pipex.output_fd);
	free_pipex(&pipex);
	return (0);
}
