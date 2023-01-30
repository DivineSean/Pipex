/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:20:21 by markik            #+#    #+#             */
/*   Updated: 2023/01/28 06:26:07 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

char	**ft_split(char *s, char c)
{
	char	**str;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	str = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!str)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			str[i] = ft_word(s, c);
			if (!(str[i]))
				return (ft_free(str, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strpipex(char *s, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == str[j])
		{
			if (j == ft_strlen(str) - 1)
				return (s + i + 2);
			i++;
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_strcat(char *str, char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[j])
	{
		str[i] = dest [i];
		i++;
		j++;
	}
	j = 0;
	while (src[j])
	{
		str[i] = src[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	*ft_strjoiness(char *s1, char *s2)
{
	size_t	len;
	char	*str;

	if (!s1 || !s2)
		return (0);
	len = ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	str = (char *)malloc(sizeof (char) * len);
	if (!str)
		return (0);
	ft_strcat(str, s1, s2);
	return (str);
}

char	*ft_strchr_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		if (ft_strpipex(env[i], "PATH"))
		{
			path = ft_strpipex(env[i], "PATH");
			return (path);
		}
		i++;
	}
	return (0);
}
