/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:16:31 by dle-fur           #+#    #+#             */
/*   Updated: 2025/01/23 11:05:22 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libraries/libft/libft.h"

/*-----------------------------------------------*/

typedef struct s_pipex
{
	char	*input_file;
	char	*output_file;
	char	**cmd1;
	char	**cmd2;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	pid_t	pid_child;
	pid_t	pid_parent;

}	t_pipex;

/*-----------------------------------------------*/

//utils
void	free_c(char **str);
void	free_pipex(t_pipex *pipex);

//check_error
int		check_args(int argc, char **argv);
int		check_files(t_pipex *pipex);
void	handle_command_error(char **path, char *cmd_path);
int		ft_isspace(int c);
int		is_empty_or_whitespace(const char *str);

//find_path
char	**ft_path(char **env);
char	**get_cmd_extract(t_pipex *pipex);
int		check_execute_command(char **path, char **cmd_extract, char **env);
void	execute_command(t_pipex *pipex, char **env);

//init_pipex
int		init_pipex(t_pipex *pipex, char **argv);

//pipex
void	execute_child(t_pipex *pipex, char **env);
void	execute_parents(t_pipex *pipex, char **env);

#endif