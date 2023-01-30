/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiple_Pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 06:25:04 by markik            #+#    #+#             */
/*   Updated: 2023/01/30 05:36:54 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

char	**fd_free1(int **str, size_t j)
{
	int	i;

	i = j;
	while (i >= 0)
	{
		if (i == 0)
		{
			free(str[i]);
			str[i] = 0;
			break ;
		}
		free(str[i]);
		str[i] = 0;
		i--;
	}
	free(str);
	str = 0;
	return (0);
}

int	**secomde_malloc_pipe(int argc)
{
	int	**fd;
	int	x;

	x = 0;
	fd = malloc(sizeof(int *) * (argc - 4));
	if (!fd)
		exit(1);
	while (x < argc - 4)
	{
		fd[x] = malloc(sizeof(int) * 2);
		if (!fd[x])
			exit(1);
		x++;
	}
	x = 0;
	while (x < argc - 4)
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

int	main(int argc, char **argv, char **env)
{
	int		**fd;

	if (argc < 5)
		return (write(1, "You need more arg to run dis programme!!", 41), 0);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		fd = here_doc(argv[2]);
		pipex_classic(argc, argv, env, fd);
		exit(1);
	}
	fd = secomde_malloc_pipe(argc);
	fork1(argc, argv, env, fd);
	exit(1);
}
