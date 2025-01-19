/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:05:46 by david             #+#    #+#             */
/*   Updated: 2025/01/19 13:29:52 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc)
{
	if (argc != 5)
	{
		ft_printf("Usage : ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	return (0);
}

int	check_files(t_pipex *pipex)
{
	if (access(pipex->input_file, F_OK) || access(pipex->input_file, R_OK))
	{
		perror("Error: The input file does not exist or is not readable\n");
		return (1);
	}
	pipex->input_fd = open(pipex->input_file, O_RDONLY);
	if (pipex->input_fd == -1)
	{
		perror("Error input : permission denied\n");
		return (1);
	}
	pipex->output_fd = open(pipex->output_file, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (pipex->output_fd == -1)
	{
		perror("Error output: the file cannot be read or created\n");
		close(pipex->output_fd);
		return (1);
	}
	return (0);
}

void	handle_command_error(char **path, char *cmd_path)
{
	perror("Error: command not found\n");
	if (path != NULL)
		free_c(path);
	if (cmd_path != NULL)
		free(cmd_path);
}

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
