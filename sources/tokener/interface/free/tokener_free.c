/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:36 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/03 16:20:37 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Frees a single token and its contents
 * @param token Pointer to the token to free
 */
void	free_single_token(t_token *token)
{
	int	i;

	if (!token)
		return ;
	if (token->value)
		free(token->value);
	if (token->split_values)
	{
		i = 0;
		while (token->split_values[i])
		{
			free(token->split_values[i]);
			i++;
		}
		free(token->split_values);
		token->split_values = NULL;
	}
	if (token->filepath)
		free(token->filepath);
	free(token);
}

/**
 * Frees the entire token linked list
 * @param tokens Pointer to the head of the token list
 */
void	free_token_struct(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free_single_token(current);
		current = NULL;
		current = next;
	}
	*tokens = NULL;
}
