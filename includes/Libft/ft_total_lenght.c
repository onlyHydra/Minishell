/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_total_lenght.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:57:18 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 20:02:59 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculate the total length of the arguments
 * @param argv: The command line arguments
 * @return: The total length of the arguments string
 */
int	calculate_total_length(char **argv)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 1;
	while (argv[i])
	{
		total_len += ft_strlen(argv[i]);
		if (argv[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}
