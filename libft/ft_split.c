/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:45:42 by absela            #+#    #+#             */
/*   Updated: 2023/03/04 16:00:31 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checksepa(char c, char sep)
{
	if (c == sep)
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

static int	countword(char *str, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (checksepa(str[i], c) == 0 && checksepa(str[i + 1], c) == 1)
			w++;
		i++;
	}
	return (w);
}

static void	cpyword(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (checksepa(s2[i], c) == 0)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

static int	ft_split1(char **split, char *str, char c, int k)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (checksepa(str[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (checksepa(str[i + j], c) == 0)
				j++;
			split[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (!(split + k))
				return (0);
			cpyword(split[k], str + i, c);
			i += j;
			k++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		w;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (countword((char *)s, c) + 1));
	if (!str)
		return (NULL);
	w = 0;
	if (!ft_split1(str, (char *)s, c, 0))
	{
		while (str + w)
		{
			free(str + w);
			w++;
		}
		free(str);
	}
	str[countword((char *)s, c)] = 0;
	free((char *)s);
	return (str);
}
