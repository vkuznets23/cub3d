/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:14:19 by vkuznets          #+#    #+#             */
/*   Updated: 2024/04/26 14:13:26 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	s;
	void	*p;

	s = count * size;
	if (count && size > SIZE_MAX / count)
		return (0);
	p = malloc(s);
	if (!p)
		return (0);
	else
		ft_bzero(p, s);
	return (p);
}
