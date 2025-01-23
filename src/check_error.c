/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:05:46 by david             #+#    #+#             */
/*   Updated: 2025/01/23 11:05:14 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_printf("Usage : ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	if (is_empty_or_whitespace(argv[2]))
	{
		ft_printf("Error: First command is empty or whitespace only.\n");
		return (1);
	}
	if (is_empty_or_whitespace(argv[3]))
	{
		ft_printf("Error: Second command is empty or whitespace only.\n");
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

int	ft_isspace(int c)
{
	return ((c == ' ')
		|| (c >= 9 && c <= 13));
}

int	is_empty_or_whitespace(const char *str)
{
	if (!str)
		return (1);
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	return (*str == '\0');
}
