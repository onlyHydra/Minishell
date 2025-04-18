/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Tokenize the argv input with command identification
 * @param argv: The command line arguments
 * @return: Parsed data array
 */
t_parsed_data	*tokenize_data(char **argv)
{
	int		total_len;
	char	*input_str;
	t_token	*tokens;

	if (!argv || !argv[1])
		return (NULL);
	total_len = calculate_total_length(argv);
	input_str = concatenate_arguments(argv, total_len);
	if (!input_str)
		return (NULL);
	tokens = tokenize_string(input_str);
	free(input_str);
	if (!tokens)
		return (NULL);
	return (tokens_to_parsed_data(tokens));
}
