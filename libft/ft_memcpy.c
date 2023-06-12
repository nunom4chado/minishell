/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:27:45 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/09 16:45:11 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t	n)
{
	size_t	l;

	if (!dest && !src)
		return (0);
	l = 0;
	while (l < n)
	{
		((unsigned char *)dest)[l] = ((unsigned char *)src)[l];
		l++;
	}
	return (dest);
}
