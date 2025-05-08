/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:00:19 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:46:35 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/abstract_syntax_tree.h"

t_node	*parse_expression(t_parsed_data **tokens)
{
	if (tokens == NULL || *tokens == NULL || (*tokens)->data == NULL)
		return (NULL);
	return (parser_or(tokens));
}
