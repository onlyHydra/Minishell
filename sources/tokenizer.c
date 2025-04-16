/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 15:37:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Get the token type based on the character
 * @param c: The character to check
 * @return: The token type enum value
 */
static t_token_type	get_token_type(char c)
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
 * Handles parsing of quoted strings
 * @param str: The string to parse
 * @param i: Current index in the string
 * @param quote_type: Type of quote (single or double)
 * @return: The ending index of the quoted string
 */
static int	handle_quoted_string(char *str, int i, t_token_type quote_type)
{
	char	quote_char;

	quote_char = (quote_type == SINGLE_QUOTE) ? '\'' : '"';
	i++; // Skip the opening quote
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == quote_char)
		i++; // Skip the closing quote
	return (i);
}

/**
 * Extract a token from the input string
 * @param input: The input string
 * @param start: Start index
 * @param end: End index
 * @return: The extracted token as a string
 */
static char	*extract_token(char *input, int start, int end)
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
static t_token	*add_token(t_token **head, char *value, t_token_type type)
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
static t_parsed_data	*tokens_to_parsed_data(t_token *tokens)
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
 * Tokenize a single command string
 * @param input: The input string to tokenize
 * @return: Linked list of tokens
 */
static t_token	*tokenize_string(char *input)
{
	t_token			*tokens;
	int				i;
	int				start;
	int				end;
	t_token_type	quote_type;
	t_token_type	type;

	tokens = NULL;
	i = 0;
	start = 0;
	while (input[i])
	{
		// Skip whitespace
		if (input[i] == ' ' || input[i] == '\t')
		{
			if (start < i)
				add_token(&tokens, extract_token(input, start, i), CMD);
			i++;
			start = i;
			continue ;
		}
		// Handle quotes
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_type = (input[i] == '\'') ? SINGLE_QUOTE : DOUBLE_QUOTE;
			end = handle_quoted_string(input, i, quote_type);
			// Extract the quoted string with quotes
			add_token(&tokens, extract_token(input, i, end), quote_type);
			i = end;
			start = i;
			continue ;
		}
		// Handle operators
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			// Add previous token if exists
			if (start < i)
				add_token(&tokens, extract_token(input, start, i), CMD);
			type = get_token_type(input[i]);
			// Check for double operators (>>, <<)
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
					&& input[i + 1] == '<'))
			{
				type = (input[i] == '>') ? REDIRECT_APPEND : HEREDOC;
				add_token(&tokens, extract_token(input, i, i + 2), type);
				i += 2;
			}
			else
			{
				add_token(&tokens, extract_token(input, i, i + 1), type);
				i++;
			}
			start = i;
			continue ;
		}
		if (input[i] == '$')
		{
			if (start < i)
				add_token(&tokens, extract_token(input, start, i), CMD);
			end = i + 1;
			while (input[end] && (ft_isalnum(input[end]) || input[end] == '_'))
				end++;
			if (input[i + 1] == '?')
			{
				add_token(&tokens, extract_token(input, i, i + 2), EXIT_STATUS);
				end = i + 2;
			}
			else
				add_token(&tokens, extract_token(input, i, end), ENV_VAR);
			i = end;
			start = i;
			continue ;
		}
		i++;
	}
	// Add the last token if exists
	if (start < i)
		add_token(&tokens, extract_token(input, start, i), CMD);
	return (tokens);
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
		ft_strlcat(input_str, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			ft_strlcat(input_str, " ", ft_strlen(" "));
		i++;
	}
	// Tokenize the input string
	tokens = tokenize_string(input_str);
	// Convert tokens to parsed_data
	parsed_data = tokens_to_parsed_data(tokens);
	// Free the input string and tokens
	free(input_str);
	return (parsed_data);
}
