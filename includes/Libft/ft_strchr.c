/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:11:56 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 14:52:08 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s1, int c)
{
	while (*s1 != (char)c)
		if (!*s1++)
			return (NULL);
	return ((char *)s1);
}
// int	main(void)
// {
// 	char	*s = NULL;
// 	char	c;

// 	c = 's';
// 	printf("ft: %s\n", ft_strchr(((void*)0), '\0'));
// }