/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:00:19 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 21:58:59 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

t_node	*parse_expression(t_parsed_data **tokens)
{
	if (tokens == NULL || *tokens == NULL || (*tokens)->data == NULL)
		return (NULL);
    return (parser_or(tokens));
}
