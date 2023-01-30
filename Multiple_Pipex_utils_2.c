/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiple_Pipex_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 03:33:45 by markik            #+#    #+#             */
/*   Updated: 2023/01/29 03:34:16 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || str1[i] == 0 || str2[i] == 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	close_fd_wait(pid_t pid1, pid_t pid2, int argc, int **fd)
{
	int	x;

	x = 0;
	while (x < argc - 4)
	{
		close(fd[x][1]);
		close(fd[x][0]);
		x++;
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	fork1(int argc, char **argv, char **env, int **fd)
{
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;

	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork: child 1 killed :"));
	else if (pid1 == 0)
		child3(argc, argv, env, fd);
	else
	{	
		pid2 = fork2(argc, argv, env, fd);
		pid3 = fork3(argc, argv, env, fd);
		close_fd_wait(pid1, pid2, argc, fd);
		waitpid(pid3, NULL, 0);
	}
	return ;
}
