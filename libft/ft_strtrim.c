/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 07:54:17 by absela            #+#    #+#             */
/*   Updated: 2023/03/04 16:00:45 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chehcker(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	int		i;
	int		d;
	int		f;
	char	*str;

	d = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[d] && ft_chehcker(set, s1[d]))
		d++;
	f = ft_strlen(s1) - 1;
	while (f >= d && ft_chehcker(set, s1[f]))
		f--;
	str = (char *)malloc(f - d + 2);
	if (!str)
		return (NULL);
	while (d <= f)
	{
		str[i] = s1[d];
		i++;
		d++;
	}
	str[i] = '\0';
	return (str);
}
