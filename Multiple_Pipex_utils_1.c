/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiple_Pipex_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:31:58 by markik            #+#    #+#             */
/*   Updated: 2023/01/29 03:33:34 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	child3(int argc, char **argv, char **env, int **fd)
{
	int	redirect_fd;
	int	x;

	x = 0;
	redirect_fd = open(argv[1], O_RDONLY, 0777);
	if (redirect_fd == -1)
		perror(argv[1]);
	if (dup2(redirect_fd, STDIN_FILENO) == -1)
		perror("Dup2 infile");
	close(redirect_fd);
	if (dup2(fd[x][1], STDOUT_FILENO) == -1)
		perror("second dup2 failled");
	while (x < argc - 4)
	{
		close(fd[x][1]);
		close(fd[x][0]);
		x++;
	}
	exec_cmd(argv[2], env);
	return ;
}

void	child4(int argc, int **fd, int x)
{
	int	i;

	i = 0;
	if (dup2(fd[x][0], STDIN_FILENO) == -1)
		perror("First Dup2 failled");
	if (dup2(fd[x + 1][1], STDOUT_FILENO) == -1)
		perror("second dup2 failled");
	while (i < argc - 4)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
	return ;
}

void	child5(int argc, char **argv, int **fd)
{
	int	redirect_fd;
	int	i;

	i = 0;
	redirect_fd = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (redirect_fd == -1)
		return (perror(argv[argc - 1]));
	if (dup2(redirect_fd, STDOUT_FILENO) == -1)
		perror("third Dup2 failled");
	close(redirect_fd);
	if (dup2(fd[argc - 5][0], STDIN_FILENO) == -1)
		perror("Last Dup2 failled");
	while (i < argc - 4)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;
	}
	return ;
}

pid_t	fork2(int argc, char **argv, char **env, int **fd)
{
	int		x;
	pid_t	pid2;

	x = 0;
	while (x < argc - 5)
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("fork: child 2 killed :"), 0);
		else if (pid2 == 0)
		{
			child4(argc, fd, x);
			exec_cmd(argv[x + 3], env);
		}
		x++;
	}
	return (pid2);
}

pid_t	fork3(int argc, char **argv, char **env, int **fd)
{
	pid_t	pid3;

	pid3 = fork();
	if (pid3 == -1)
		return (perror("fork: child 2 killed :"), 0);
	else if (pid3 == 0)
	{
		child5(argc, argv, fd);
		exec_cmd(argv[argc - 2], env);
	}
	return (pid3);
}
