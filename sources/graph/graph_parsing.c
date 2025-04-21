/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:00:19 by schiper           #+#    #+#             */
/*   Updated: 2025/04/21 22:26:38 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_functions.h"

t_node	*parse_expression(t_parsed_data **tokens)
{
	t_node *node;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	node = parse_or(tokens);
	if (node != NULL)
		return (node);
	node = parse_and(tokens);
	if (node != NULL)
		return (node);
	node = parse_pipe(tokens);
	if (node != NULL)
		return (node);
	node = parser_command(tokens);
	return (node);
}

t_node			*parser_or(t_parsed_data **tokens)
{
    t_node *left;
    t_node *right;
    
    left = parse_expression(tokens);
    if (left == NULL)
        return NULL;
}

t_node *parser_or(t_parsed_data **tokens)
{
    t_node *left;
    t_node *right;

    // Step 1: Parse the left-hand side expression (it could be a command or an AND operation)
    left = parser_and(tokens); // This handles ANDs first, or if no AND, it falls back to commands
    if (left == NULL)
        return NULL;  // If parsing the left side fails, return NULL.

    // Step 2: Look ahead for an OR operator (||)
    while (peek_token(tokens) != NULL && peek_token(tokens)->type == OR)
    {
        // Step 3: Consume the OR operator
        advance_token(tokens);

        // Step 4: Parse the right-hand side expression after the OR
        right = parser_and(tokens);  // We again look for ANDs first, before the right part of OR
        if (right == NULL)
        {
            free_ast(left);
            return NULL;  // If we can't parse the right side, free the left side and return NULL
        }

        // Step 5: Create a binary node for the OR operation connecting the left and right subtrees
        t_node *or_node = create_binary_node(NODE_OR, left, right);
        left = or_node;  // Set the newly created OR node as the new left to handle additional ORs
    }

    // Step 6: If no OR operator was found, return the left expression (it may be a command or an AND expression)
    return left;
}