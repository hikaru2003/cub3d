/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:55:41 by hmorisak          #+#    #+#             */
/*   Updated: 2023/09/10 18:37:55 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check(char **array, size_t i)
{
	if (array[i] == NULL)
	{
		while (i != 0)
		{
			free(array[i]);
			i--;
		}
		free(array[i]);
		free(array);
		return (1);
	}
	return (0);
}

static int	sep_count(char const *s, char c)
{
	int	strlen;
	int	count;
	int	i;

	strlen = 0;
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (strlen != 0)
				count++;
			strlen = 0;
		}
		else
			strlen++;
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static char	**do_it(const char *s, char c, char **array)
{
	size_t	strlen;
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			strlen = 0;
			while (*s != '\0' && *s != c)
			{
				strlen++;
				s++;
			}
			array[i] = ft_substr(s - strlen, 0, strlen);
			if (check(array, i) == 1)
				return (NULL);
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (sep_count(s, c) + 1));
	if (!array)
		return (NULL);
	array = do_it(s, c, array);
	return (array);
}

// #include <stdio.h>
// int main(void)
// {
// 	// char const str[] = tab = ft_split("     ", ' ');;
// 	// char charset = ' ';
// 	// char **tmp = ft_split(str, charset);

// 	// int i = 0;
// 	// while (tmp[i] != NULL)
// 	// // {
// 	// 	printf("%s\n", tmp[i]);
// 	// 	i++;
// 	// }

// 	char **tab;
// 	tab = ft_split("", ' ');
// 	printf("%s\n", *tab);
// 	return (0);
// }