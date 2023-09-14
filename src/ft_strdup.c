/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:44:55 by hmorisak          #+#    #+#             */
/*   Updated: 2023/09/11 13:36:44 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	slen;
	int		i;

	slen = ft_strlen((char *)s1);
	tmp = (char *)malloc(sizeof(char) * (slen + 1));
	if (!tmp)
		print_error("bad_alloc");
	i = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

// #include <stdio.h>
// int	main(void)
// {
// 	const char s1[] = "helloworld";
// 	printf("%s\n", ft_strdup(s1));

// 	return (0);
// }