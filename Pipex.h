/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:16:47 by markik            #+#    #+#             */
/*   Updated: 2023/01/30 05:36:09 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strchr(char *s, int c);
char	*ft_reading_to_stock(int fd, char *stock);
char	*ft_liner(char *stock);
char	*ft_stockage(char *stock);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_count_word(char *s, char c);
size_t	ft_strlen_checker(char *s, char c);
char	**ft_free(char **str, size_t j);
char	*ft_word(char *s, char c);
char	**ft_split(char *s, char c);
char	*ft_strpipex(char *s, char *str);
void	ft_strcat(char *str, char *dest, char *src);
char	*ft_strjoiness(char *s1, char *s2);
char	*ft_strchr_path(char **env);
char	*ft_cmdpath(char **command, char **env);
void	exec_cmd(char *argv, char **env);
void	child1(char **argv, char **env, int *fd);
void	child2(char **argv, char **env, int *fd);
void	child3(int argc, char **argv, char **env, int **fd);
void	child4(int argc, int **fd, int x);
void	child5(int argc, char **argv, int **fd);
pid_t	fork2(int argc, char **argv, char **env, int **fd);
pid_t	fork3(int argc, char **argv, char **env, int **fd);
void	close_fd_wait(pid_t pid1, pid_t pid2, int argc, int **fd);
void	fork1(int argc, char **argv, char **env, int **fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		**here_doc(char *argv);
void	child_doc(char **argv, char **env, int **fd);
void	child2_doc(char **argv, char **env, int **fd);
int		pipex_classic(int argc, char **argv, char **env, int **fd);
int		**malloc_pipe(void);
#endif
