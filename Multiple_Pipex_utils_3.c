/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiple_Pipex_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:37:12 by markik            #+#    #+#             */
/*   Updated: 2023/01/30 05:41:51 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	child_doc(char **argv, char **env, int **fd)
{
	int	x;

	x = 0;
	if (dup2(fd[0][0], STDIN_FILENO) == -1)
		perror("First dup2 failled");
	if (dup2(fd[1][1], STDOUT_FILENO) == -1)
		perror("second dup2 failled");
	while (x < 2)
	{
		close(fd[x][0]);
		close(fd[x][1]);
		x++;
	}
	exec_cmd(argv[3], env);
	return ;
}

void	child2_doc(char **argv, char **env, int **fd)
{
	int	redirect_fd;
	int	x;

	x = 0;
	redirect_fd = open(argv[5], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (redirect_fd == -1)
	{
		perror(argv[5]);
		exit(1);
	}
	if (dup2(redirect_fd, STDOUT_FILENO) == -1)
		perror("third Dup2 failled");
	close(redirect_fd);
	if (dup2(fd[1][0], STDIN_FILENO) == -1)
		perror("Last Dup2 failled");
	while (x < 2)
	{
		close(fd[x][0]);
		close(fd[x][1]);
		x++;
	}
	exec_cmd(argv[4], env);
	return ;
}

int	pipex_classic(int argc, char **argv, char **env, int **fd)
{
	pid_t	pid1;
	pid_t	pid2;

	pid2 = 0;
	if (argc - 4 != 2)
		return (write(1, "You did more or less arg, try again!!", 38), 0);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork: child 1 killed :"), 0);
	else if (pid1 == 0)
		child_doc(argv, env, fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("fork: child 2 killed :"), 0);
		else if (pid2 == 0)
			child2_doc(argv, env, fd);
	}
	close_fd_wait(pid1, pid2, 6, fd);
	return (0);
}

int	**malloc_pipe(void)
{
	int	x;
	int	**fd;

	fd = malloc(sizeof(int *) * (2));
	if (!fd)
		exit(1);
	x = 0;
	while (x < 2)
	{
		fd[x] = malloc(sizeof(int) * 2);
		if (!fd[x])
			exit(1);
		x++;
	}
	x = 0;
	while (x < 2)
	{
		if (pipe(fd[x]) == -1)
		{
			perror("Pipe Problem :");
			exit (1);
		}
		x++;
	}
	return (fd);
}

int	**here_doc(char *argv)
{
	char	*buffer;
	char	*stop_sign;
	int		**fd;

	fd = malloc_pipe();
	stop_sign = ft_strjoiness(argv, "\n");
	while (1)
	{
		write(2, "pipe heredoc> ", 15);
		buffer = get_next_line(0);
		if (buffer == NULL || \
		!ft_strncmp(buffer, stop_sign, ft_strlen(stop_sign)))
		{
			free(stop_sign);
			free(buffer);
			break ;
		}
		write(fd[0][1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (fd);
}
