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
 * Process a normal token and add it to the token list
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 */
// void process_token(char *input, t_parse_state *state, int end)
// {
//     char *token_value;
//     char *processed_token;
//     t_token_type token_type;

//     token_value = extract_token(input, state->start, end);
//     processed_token = handle_escapes(token_value);
//     free(token_value);
//     if (processed_token && processed_token[0] == '-')
//         token_type = FLAG;
//     else
//         token_type = CMD;

//     add_token(state->tokens, processed_token, token_type);
//     state->in_word = 0;
// }

/**
 * Get the token type based on the character
 * @param c: The character to check
 * @return: The token type enum value
 */
t_token_type	get_token_type(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (REDIRECT_OUT);
	else if (c == '<')
		return (REDIRECT_IN);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '-')
		return (FLAG);
	else
		return (CMD);
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
