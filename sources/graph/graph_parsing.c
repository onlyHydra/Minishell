/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:00:19 by schiper           #+#    #+#             */
/*   Updated: 2025/04/21 22:04:52 by schiper          ###   ########.fr       */
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
