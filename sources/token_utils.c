/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:01:27 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 18:01:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Check if a character is an operator
 * @param c: The character to check
 * @return: 1 if it's an operator, 0 otherwise
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

/**
 * Extract a token from the input string
 * @param input: The input string
 * @param start: Start index
 * @param end: End index
 * @return: The extracted token as a string
 */
char	*extract_token(char *input, int start, int end)
{
	int		len;
	char	*token;
	int		i;

	len = end - start;
	token = (char *)malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (start < end)
		token[i++] = input[start++];
	token[i] = '\0';
	return (token);
}

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
