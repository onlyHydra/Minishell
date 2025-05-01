/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:30:23 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 21:06:08 by schiper          ###   ########.fr       */
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

int	is_operator_token(t_parsed_data *token)
{
	t_token_type	type;

	if (!token || !token->token)
		return (0);
	type = *(token->token);
	if (type == PIPE || type == AND || type == OR || type == LPAREN
		|| type == RPAREN)
		return (1);
	return (0);
}

t_token_type	*peek_token_label(t_parsed_data **data)
{
	return ((*data)->token);
}
