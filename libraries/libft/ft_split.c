/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:54:02 by david             #+#    #+#             */
/*   Updated: 2025/01/19 10:42:15 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
			{
				i++;
			}
			if (s[i] == '\0')
			{
				return (count);
			}
		}
		i++;
	}
	return (count);
}

static char	*cut_word(char const *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	if (end <= start)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (word == NULL)
	{
		return (NULL);
	}
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	*ft_free(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	size_t		i;
	int			index;
	int			j;

	tab = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	index = -1;
	j = 0;
	i = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			tab[j] = cut_word(s, index, i);
			if (tab[j++] == NULL)
				return (ft_free(tab));
			index = -1;
		}
	}
	tab[j] = NULL;
	return (tab);
}
