/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:26:11 by markik            #+#    #+#             */
/*   Updated: 2023/01/28 08:07:31 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	ft_free_strs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*ft_cmdpath(char **command, char **env)
{
	char	*str;
	char	**path_splied;
	char	*path;
	int		i;

	str = ft_strchr_path(env);
	path_splied = ft_split(str, ':');
	if (!path_splied)
		return (0);
	i = 0;
	while (path_splied[i])
	{
		path = ft_strjoiness(ft_strjoiness(path_splied[i], "/"), command[0]);
		if (access((const char *)path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (access((const char *)path, F_OK) == -1)
		return (ft_free_strs(path_splied), NULL);
	i = 0;
	ft_free_strs(path_splied);
	return (path);
}

void	exec_cmd(char *argv, char **env)
{
	char	**command;

	command = ft_split(argv, ' ');
	if (ft_strpipex(command[0], "./"))
	{
		if (execve(command[0], command, NULL) == -1)
		{
			perror(command[0]);
			exit(1);
		}
	}
	else if (ft_cmdpath(command, env))
		command[0] = ft_cmdpath(command, env);
	if ((ft_strpipex(command[0], "/")) && access(command[0], X_OK) == 0)
	{
		if (execve(command[0], command, NULL) == -1)
		{
			perror(command[0]);
			exit(1);
		}
	}
	else
		perror(command[0]);
	return ;
}

void	child1(char **argv, char **env, int *fd)
{
	int		redirect_fd;

	redirect_fd = open(argv[1], O_RDONLY, 0777);
	if (redirect_fd == -1)
		perror(argv[1]);
	if (dup2(redirect_fd, STDIN_FILENO) == -1)
		perror("First Dup2 failled");
	close(redirect_fd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("second dup2 failled");
	close(fd[1]);
	close(fd[0]);
	exec_cmd(argv[2], env);
	return ;
}

void	child2(char **argv, char **env, int *fd)
{
	int	redirect_fd;

	redirect_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (redirect_fd == -1)
	{
		perror(argv[4]);
		exit(1);
	}
	if (dup2(redirect_fd, STDOUT_FILENO) == -1)
		perror("third Dup2 failled");
	close(redirect_fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("Last Dup2 failled");
	close(fd[0]);
	close(fd[1]);
	exec_cmd(argv[3], env);
	return ;
}
