/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_inferface1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:02:35 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 18:14:33 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_struct.h"
#include <stdlib.h>

/**
 * Add a token to the linked list of tokens
 * @param head: Pointer to the head of the token list
 * @param value: The token string value
 * @param type: The token type
 * @return: The new token added
 */
t_token	*add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	current = (t_token *)malloc(sizeof(t_token));
	if (!current)
	{
		free(new_token);
		return (NULL);
	}
	new_token->value = value;
	new_token->split_values = NULL;
	new_token->type = type;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
	return (new_token);
}

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
	int count;
	t_token *current;

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