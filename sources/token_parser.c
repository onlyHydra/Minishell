/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:02:35 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 13:29:26 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Allocate and fill the parsed_data array based on the tokens
 * @param tokens: The linked list of tokens
 * @param count: The number of tokens
 * @return: An array of parsed_data structures
 */
t_parsed_data	*allocate_parsed_data(t_token *tokens, int count)
{
	t_token			*current;
	t_parsed_data	*parsed_data;
	int				i;

	i = -1;
	current = tokens;
	parsed_data = malloc(sizeof(t_parsed_data) * (count + 1));
	if (!parsed_data)
		return (NULL);
	while (++i < count)
	{
		parsed_data[i].token = malloc(sizeof(t_token_type));
		if (!parsed_data[i].token)
			return (NULL);
		*(parsed_data[i].token) = current->type;
		parsed_data[i].data = ft_strdup(current->value);
		current = current->next;
	}
	parsed_data[count] = (t_parsed_data){NULL, NULL};
	return (parsed_data);
}

/**
 * Convert the linked list of tokens to an array of parsed data
 * @param tokens: The linked list of tokens
 * @return: Array of parsed_data structures
 */
t_parsed_data	*tokens_to_parsed_data(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	if (count == 0)
		return (NULL);
	return (allocate_parsed_data(tokens, count));
}
