/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:38:51 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 16:02:20 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_len_matrix(const void **matrix)
{
	unsigned int	size;

	size = 0;
	while (matrix != NULL && matrix[size] != NULL)
		size++;
	return (size);
}
