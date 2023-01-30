/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex_M.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:33:02 by markik            #+#    #+#             */
/*   Updated: 2023/01/28 08:06:44 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	pid2 = 0;
	if (argc - 4 != 1)
		return (write(1, "few or more arg!!", 18), 0);
	if (pipe(fd) == -1)
		return (perror("Pipe Problem :"), 0);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork: child 1 killed :"), 0);
	else if (pid1 == 0)
		child1(argv, env, fd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			return (perror("fork: child 2 killed :"), 0);
		else if (pid2 == 0)
			child2(argv, env, fd);
	}
	close(fd[0]);
	close(fd[1]);
	return (waitpid(pid1, NULL, 0), waitpid(pid2, NULL, 0), 0);
}
