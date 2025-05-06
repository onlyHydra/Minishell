/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:02:35 by marvin            #+#    #+#             */
/*   Updated: 2025/05/02 19:08:31 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"
#include <stdlib.h>

/**
 * Helper function to allocate token and set its type
 * @param parsed_data: Array of parsed data
 * @param index: Current index
 * @param type: Token type to set
 * @return: 1 on success, 0 on error
 */
static int	allocate_token_type(t_parsed_data *parsed_data, int index,
		t_token_type type)
{
	parsed_data[index].token = malloc(sizeof(t_token_type));
	if (!parsed_data[index].token)
	{
		free_parsed_data_on_error(parsed_data, index, 0);
		return (0);
	}
	*(parsed_data[index].token) = type;
	return (1);
}

// /**
//  * Allocate and fill the parsed_data array based on the tokens
//  * @param tokens: The linked list of tokens
//  * @param count: The number of tokens
//  * @return: An array of parsed_data structures
//  */
// t_parsed_data	*allocate_parsed_data(t_token *tokens, int count)
// {
// 	t_token			*current;
// 	t_parsed_data	*parsed_data;
// 	int				i;

// 	i = -1;
// 	current = tokens;
// 	parsed_data = malloc(sizeof(t_parsed_data) * (count + 1));
// 	parsed_data->filepath = NULL;
// 	if (!parsed_data)
// 		return (NULL);
// 	while (++i < count && current)
// 	{
// 		if (!allocate_token_type(parsed_data, i, current->type))
// 			return (NULL);
// 		parsed_data[i].data = ft_strdup(current->value);
// 		parsed_data[i].filepath = ft_strdup(current->filepath);
// 		if (!parsed_data[i].data && current->value)
// 		{
// 			free_parsed_data_on_error(parsed_data, i, 1);
// 			return (NULL);
// 		}
// 		current = current->next;
// 	}
// 	parsed_data[count] = (t_parsed_data){NULL, NULL, NULL};
// 	return (parsed_data);
// }

/**
 * Helper function to allocate and fill a parsed_data entry
 * @param parsed_data: Array to fill
 * @param i: Current index
 * @param current: Current token
 * @return: 1 on success, 0 on failure
 */
static int	fill_token_data(t_parsed_data *parsed_data, int i, t_token *current)
{
	if (!allocate_token_type(parsed_data, i, current->type))
		return (0);
	if (current->value)
	{
		parsed_data[i].data = ft_strdup(current->value);
		if (current->filepath != NULL)
			parsed_data[i].filepath = ft_strdup(current->filepath);
		if (!parsed_data[i].data)
		{
			free_parsed_data_on_error(parsed_data, i, 1);
			return (0);
		}
	}
	return (1);
}

/**
 * Convert the linked list of tokens to an array of parsed data
 * @param tokens: The linked list of tokens
 * @return: Array of parsed_data structures
 */
t_parsed_data	*tokens_to_parsed_data(t_token *tokens)
{
	int				count;
	t_token			*current;
	t_parsed_data	*parsed_data;
	int				i;

	if (!tokens)
		return (NULL);
	count = 0;
	current = tokens;
	while (current && ++count)
		current = current->next;
	parsed_data = malloc(sizeof(t_parsed_data) * (count + 1));
	if (!parsed_data)
		return (NULL);
	ft_memset(parsed_data, 0, sizeof(t_parsed_data) * (count + 1));
	current = tokens;
	i = -1;
	while (++i < count && current)
	{
		if (!fill_token_data(parsed_data, i, current))
			return (NULL);
		current = current->next;
	}
	return (parsed_data);
}
