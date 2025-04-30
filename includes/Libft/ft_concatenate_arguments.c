/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concatenate_arguments.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:58:30 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 19:58:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
