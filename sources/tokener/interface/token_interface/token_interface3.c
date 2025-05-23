/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:30:23 by schiper           #+#    #+#             */
/*   Updated: 2025/05/19 18:22:20 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models/token_struct.h"

t_parsed_data	*peek_token(t_parsed_data **tokens)
{
	if (tokens == NULL || *tokens == NULL)
		return (NULL);
	return (*tokens);
}

void	advance_token(t_parsed_data **tokens)
{
	if (tokens == NULL || *tokens == NULL)
		return ;
	(*tokens)++;
}

int	is_operator_token(t_token_type type)
{
	if (!type)
		return (0);
	if (type == PIPE || type == AND || type == OR || type == LPAREN
		|| type == RPAREN)
		return (1);
	return (0);
}

int	is_operator_token_xd(t_token_type type)
{
	if (!type)
		return (0);
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

t_token_type	*peek_token_label(t_parsed_data **data)
{
	if (data == NULL || *data == NULL)
		return (NULL);
	return ((*data)->token);
}
