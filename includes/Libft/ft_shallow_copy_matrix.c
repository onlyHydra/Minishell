/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shallow_copy_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:02:25 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 18:37:41 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_shallow_copy_matrix(void **dest, void **src)
{
	int	index;

	if (!dest || !src)
		return (-1);
	index = 0;
	while (src[index] != NULL)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = NULL;
	return (0);
}
