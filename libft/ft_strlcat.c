/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:22:31 by hmorisak          #+#    #+#             */
/*   Updated: 2022/11/16 17:40:44 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	if (!src)
		slen = ft_strlen((char *)src);
	slen = ft_strlen((char *)src);
	if (!dst && dstsize == 0)
		return (slen);
	if (dstsize == 0)
		return (slen);
	dlen = ft_strlen(dst);
	i = 0;
	if (dstsize <= dlen)
		return (dstsize + slen);
	while (i < dstsize - dlen - 1 && *src != '\0')
	{
		dst[dlen + i] = *src;
		i++;
		src++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	dst[30] = "hello";
// 	char	src[30] = "123456789";

// 	printf("%lu\n", strlcat(NULL, src, 0));
// 	printf("%lu\n", ft_strlcat(NULL, src, 0));
// 	// printf("%lu\n", ft_strlcat(dst, src, 0));
// 	printf("%s\n", dst);
// 	return (0);
// }