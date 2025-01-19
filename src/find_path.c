/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:38 by dle-fur           #+#    #+#             */
/*   Updated: 2025/01/19 12:14:01 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **env)
{
	int		i;
	char	*path;
	char	**f_path;

	i = 0;
	path = NULL;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			if (path == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (path == NULL)
		return (NULL);
	f_path = ft_split(path, ':');
	free(path);
	return (f_path);
}

char	**get_cmd_extract(t_pipex *pipex)
{
	if (pipex->pid_child == 0)
		return (pipex->cmd1);
	return (pipex->cmd2);
}

int	check_execute_command(char **path, char **cmd_extract, char **env)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_extract[0]);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			execve(cmd_path, cmd_extract, env);
			free(cmd_path);
			return (0);
		}
		free(cmd_path);
		i++;
	}
	return (1);
}

void	execute_command(t_pipex *pipex, char **env)
{
	char	**path;
	char	**cmd_extract;

	path = ft_path(env);
	cmd_extract = get_cmd_extract(pipex);
	if (!path || !cmd_extract || !cmd_extract[0])
	{
		if (path == NULL)
			free_c(path);
		free_pipex(pipex);
		return ;
	}
	if (check_execute_command(path, cmd_extract, env) != 0)
	{
		handle_command_error(path, NULL);
		free_pipex(pipex);
		return ;
	}
}
