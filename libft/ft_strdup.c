/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:44:55 by hmorisak          #+#    #+#             */
/*   Updated: 2022/10/12 15:21:09 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	slen;
	int		i;

	slen = ft_strlen((char *)s1);
	tmp = (char *)malloc(sizeof(char) * (slen + 1));
	if (!tmp)
		return (NULL);
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