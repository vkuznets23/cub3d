/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:06 by vkuznets          #+#    #+#             */
/*   Updated: 2024/04/26 11:31:17 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
		j++;
	if (i >= dstsize)
		j += dstsize;
	else
		j += i;
	n = 0;
	while (src[n] && (i + 1 < dstsize))
	{
		dst[i] = src[n];
		n++;
		i++;
	}
	dst[i] = '\0';
	return (j);
}
