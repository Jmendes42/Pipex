/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 05:05:40 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 03:00:15 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

static int	count(char const *s, char c)
{
	unsigned int	index;
	unsigned int	count;

	index = 0;
	count = 0;
	while (s[index])
	{
		while (s[index] == c)
			index++;
		if (s[index] != '\0')
			count++;
		while (s[index] && s[index] != c)
			index++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	index;
	size_t	index_len;

	index_len = ft_strlen(s);
	index = 0;
	if (len > (index_len - start))
		len = index_len - start;
	if (start >= index_len)
	{
		sub = (char *)malloc(sizeof(*sub));
		*sub = 0;
		return (sub);
	}
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (s[start + index] != '\0' && len > 0)
	{
		sub[index] = s[start + index];
		index++;
		len--;
	}
	sub[index] = '\0';
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	index;
	unsigned int	index_a;
	unsigned int	index_tab;
	char			**tab;

	index_a = 0;
	index_tab = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!(tab))
		return (NULL);
	tab[count(s, c)] = 0;
	while (*s && *s == c)
		s++;
	while (s[index_a])
	{
		index = index_a;
		while (s[index_a] && s[index_a] != c)
			index_a++;
		tab[index_tab++] = ft_substr(s, index, index_a - index);
		while (s[index_a] && s[index_a] == c)
			index_a++;
	}
	return (tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	index;
	unsigned int	index_b;
	char			*str;

	index = 0;
	index_b = 0;
	str = (char *)malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (str == NULL)
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	while (s2[index_b])
	{
		str[index + index_b] = s2[index_b];
		index_b++;
	}
	str[index + index_b] = '\0';
	return (str);
}
