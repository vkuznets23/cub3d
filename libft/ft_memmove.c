/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:19:33 by vkuznets          #+#    #+#             */
/*   Updated: 2024/04/24 09:09:39 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*cdst;
	char	*csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	if (!cdst && !csrc)
		return (NULL);
	if (cdst > csrc)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			cdst[i] = csrc[i];
			i--;
		}
	}
	else
	{
		i = -1;
		while (++i <= (int)len - 1)
			cdst[i] = csrc[i];
	}
	return (cdst);
}
