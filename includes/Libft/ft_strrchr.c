/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:25 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/03 06:35:46 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s1, int c)
{
	int	n;

	n = ft_strlen(s1);
	while (n >= 0)
	{
		if (s1[n] == (char)c)
			return ((char *)&s1[n]);
		n--;
	}
	return (NULL);
}
// int	main(void)
// {
// 	char s[] = "Dollar dollar dollat is what I need yea yea";
// 	char c = 'd'; // Search for the first occurrence of 'd'
// 	printf("ft: %s\nnorm: %s\n", ft_strrchr(s, c), strrchr(s, c));
// }