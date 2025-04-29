/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:20:48 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 19:27:43 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

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

/**
 * Concatenate the arguments into a single string
 * @param argv: The command line arguments
 * @param total_len: The total length of the concatenated string
 * @return: A single concatenated string of arguments
 */
char	*concatenate_arguments(char **argv, int total_len)
{
	char	*input_str;
	int		i;

	input_str = malloc(total_len + 1);
	if (!input_str)
		return (NULL);
	input_str[0] = '\0';
	i = 1;
	while (argv[i])
	{
		ft_strlcat(input_str, argv[i], total_len + 1);
		if (argv[i + 1])
			ft_strlcat(input_str, " ", total_len + 1);
		i++;
	}
	return (input_str);
}
