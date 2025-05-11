/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11                              #+#    #+#             */
/*   Updated: 2025/05/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "models/token_struct.h"
#include <stdio.h>

/**
 * Get the string representation of a token type
 * @param type The token type enum value
 * @return String representation of the token type
 */
static const char	*get_token_type_str(t_token_type type)
{
	switch (type)
	{
		case CMD:
			return ("CMD");
		case STR_LITERAL:
			return ("STR_LITERAL");
		case FILENAME:
			return ("FILENAME");
		case REDIRECT_APPEND:
			return ("REDIRECT_APPEND");
		case HEREDOC:
			return ("HEREDOC");
		case ENV_VAR:
			return ("ENV_VAR");
		case AND:
			return ("AND");
		case OR:
			return ("OR");
		case LPAREN:
			return ("LPAREN");
		case RPAREN:
			return ("RPAREN");
		case FLAG:
			return ("FLAG");
		case PIPE:
			return ("PIPE");
		case REDIRECT_IN:
			return ("REDIRECT_IN");
		case REDIRECT_OUT:
			return ("REDIRECT_OUT");
		case SEMICOLON:
			return ("SEMICOLON");
		case SINGLE_QUOTE:
			return ("SINGLE_QUOTE");
		case DOUBLE_QUOTE:
			return ("DOUBLE_QUOTE");
		default:
			return ("UNKNOWN");
	}
}

/**
 * Print a visual separator line
 */
static void	print_separator(void)
{
	printf("--------------------------------------------------------\n");
}

/**
 * Print the header for the token table
 */
static void	print_header(void)
{
	print_separator();
	printf("| %-4s | %-15s | %-25s |\n", "No.", "Type", "Value");
	print_separator();
}

/**
 * Print footer for the token table
 */
static void	print_footer(int token_count)
{
	print_separator();
	printf("Total tokens: %d\n", token_count);
	print_separator();
}

/**
 * Print split values of a token if they exist
 * @param token The token containing split values
 */
static void	print_split_values(t_token *token)
{
	int	i;

	if (!token->split_values)
		return ;
	
	i = 0;
	printf("  Split values:\n");
	while (token->split_values[i])
	{
		printf("    [%d]: '%s'\n", i, token->split_values[i]);
		i++;
	}
}

/**
 * Print filepath of a token if it exists
 * @param token The token containing filepath
 */
static void	print_filepath(t_token *token)
{
	if (token->filepath)
		printf("  Filepath: '%s'\n", token->filepath);
}

/**
 * Print detailed information about a token list
 * @param tokens The list of tokens to print
 * @return Number of tokens printed
 */
int	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		count;

	if (!tokens)
	{
		printf("No tokens to display.\n");
		return (0);
	}
	
	print_header();
	
	count = 0;
	current = tokens;
	while (current)
	{
		printf("| %-4d | %-15s | %-25s |\n", 
			count, 
			get_token_type_str(current->type),
			current->value ? current->value : "(null)");
		
		// Print extra information if available
		if (current->split_values)
			print_split_values(current);
		if (current->filepath)
			print_filepath(current);
		
		current = current->next;
		count++;
	}
	
	print_footer(count);
	return (count);
}

/**
 * Print detailed information about a parsed data list
 * @param data The list of parsed data to print
 * @return Number of items printed
 */
int	print_parsed_data(t_parsed_data *data)
{
	t_parsed_data	*current;
	int				count;

	if (!data)
	{
		printf("No parsed data to display.\n");
		return (0);
	}
	
	print_separator();
	printf("| %-4s | %-15s | %-25s |\n", "No.", "Type", "Data");
	print_separator();
	
	count = 0;
	current = data;
	while (current)
	{
		printf("| %-4d | %-15s | %-25s |\n", 
			count, 
			get_token_type_str(*(current->token)),
			current->data ? current->data : "(null)");
		
		// Print filepath if available
		if (current->filepath)
			printf("  Filepath: '%s'\n", current->filepath);
		
		current = (t_parsed_data *)current->token + 1; // Assuming tokens are packed linearly
		count++;
	}
	
	print_footer(count);
	return (count);
}
