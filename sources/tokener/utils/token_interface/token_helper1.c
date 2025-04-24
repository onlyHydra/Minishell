/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:30:23 by schiper           #+#    #+#             */
/*   Updated: 2025/04/25 01:14:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_functions.h"

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
	if (!token || !token->token)
		return (0);

	if (*(token->token) == PIPE)
		return (1);
	else if (*(token->token) == AND)
		return (1);
	else if (*(token->token) == OR)
		return (1);
	return (0);
}

