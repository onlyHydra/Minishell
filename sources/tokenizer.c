/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 17:05:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	{
		*head = new_token;
	}
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
 * Convert the linked list of tokens to an array of parsed data
 * @param tokens: The linked list of tokens
 * @return: Array of parsed_data structures
 */
t_parsed_data	*tokens_to_parsed_data(t_token *tokens)
{
	t_token			*current;
	int				count;
	t_parsed_data	*parsed_data;
	int				i;

	current = tokens;
	count = 0;
	// Count number of tokens
	while (current)
	{
		count++;
		current = current->next;
	}
	// Allocate memory for the array
	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data) * (count + 1));
	if (!parsed_data)
		return (NULL);
	// Fill the array
	current = tokens;
	i = -1;
	while (++i < count)
	{
		parsed_data[i].token = (t_token_type *)malloc(sizeof(t_token_type));
		if (!parsed_data[i].token)
			return (NULL);
		*(parsed_data[i].token) = current->type;
		parsed_data[i].data = ft_strdup(current->value);
		current = current->next;
	}
	// Null terminate the array
	parsed_data[count].token = NULL;
	parsed_data[count].data = NULL;
	return (parsed_data);
}


/**
 * Tokenize the argv input
 * @param argv: The command line arguments
 * @return: Parsed data array
 */
t_parsed_data	*tokenize_data(char **argv)
{
	int				total_len;
	int				i;
	char			*input_str;
	t_token			*tokens;
	t_parsed_data	*parsed_data;

	if (!argv || !argv[1])
		return (NULL);
	// Concatenate all argv elements into a single string
	total_len = 0;
	i = 1;
	while (argv[i])
	{
		total_len += ft_strlen(argv[i]);
		if (argv[i + 1]) // Add space between arguments
			total_len++;
		i++;
	}
	input_str = (char *)malloc(sizeof(char) * (total_len + 1));
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
	// Tokenize the input string
	tokens = tokenize_string(input_str);
	if (!tokens) // Error occurred during tokenization
	{
		free(input_str);
		return (NULL);
	}
	parsed_data = tokens_to_parsed_data(tokens);
	free(input_str);
	return (parsed_data);
}
