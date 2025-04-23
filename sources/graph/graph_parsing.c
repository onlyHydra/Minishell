/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:00:19 by schiper           #+#    #+#             */
/*   Updated: 2025/04/22 13:52:28 by schiper          ###   ########.fr       */
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

t_node *parser_or(t_parsed_data **tokens)
{
    t_node *left;
    t_node *right;

   
    left = parser_and(tokens); 
    if (left == NULL)
        return NULL;  

   
    while (peek_token(tokens) != NULL && peek_token(tokens)->token == OR)
    {
        
        advance_token(tokens);

        
        right = parser_and(tokens);  
        if (right == NULL)
        {
            free_ast(left);
            return NULL;  
        }

        t_node *or_node = create_binary_node(NODE_OR, left, right);
        left = or_node;  
    }

    return left;
}

t_node *parser_and(t_parsed_data **tokens)
{
	t_node *left;
	t_node *right;

	left = parser_pipe(tokens);
	if (left == NULL)
		return NULL;

	while (peek_token(tokens) && peek_token(tokens)->token == AND)
	{
		advance_token(tokens);
		right = parser_pipe(tokens);
		if (right == NULL)
		{
			free_ast(left);
			return NULL;
		}
		left = create_binary_node(NODE_AND, left, right);
	}
	return left;
}

t_node *parser_pipe(t_parsed_data **tokens)
{
	t_node *left;
	t_node *right;

	left = parser_command(tokens);
	if (left == NULL)
		return NULL;

	while (peek_token(tokens) && peek_token(tokens)->token == PIPE)
	{
		advance_token(tokens);
		right = parser_command(tokens);
		if (right == NULL)
		{
			free_ast(left);
			return NULL;
		}
		left = create_binary_node(NODE_PIPE, left, right);
	}
	return left;
}


t_node	*parser_command(t_parsed_data **tokens)
{
	t_cmd	*cmd;

	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	cmd = build_command(tokens);
	if (cmd == NULL)
		return (NULL);
	return create_command_node(cmd);
}


