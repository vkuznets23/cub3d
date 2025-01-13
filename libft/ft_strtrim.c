/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:44 by vkuznets          #+#    #+#             */
/*   Updated: 2024/04/23 16:36:55 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*d;
	size_t		i;
	size_t		j;

	d = 0;
	if (ft_strlen((char *)set) == 0 || ft_strlen((char *)s1) == 0)
		return (ft_strdup(s1));
	if ((char *)set != 0 || (char *)s1 != 0)
	{
		j = ft_strlen((char *)s1);
		i = 0;
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && j > i && ft_strchr(set, s1[j - 1]))
			j--;
		d = (char *)malloc(sizeof(char) * (j - i + 1));
		if (!d)
			return (0);
		ft_strlcpy(d, (char *)&s1[i], (j - i + 1));
	}
	return (d);
}
