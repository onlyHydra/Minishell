/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 02:31:51 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 18:32:52 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

/**
 * Add a token to the linked list of tokens
 * @param head: Pointer to the head of the token list
 * @param value: The token string value
 * @param type: The token type
 * @return: The new token added
 */
void	add_token(t_token **head, char *value, t_token_type type,
		char *filepath)
{
	t_token	*new_token;
	t_token	*current;

	if (!head || !value)
		return ;
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = value;
	new_token->split_values = NULL;
	new_token->type = type;
	new_token->filepath = ft_strdup(filepath);
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		// if(syntax_check(current,new_token))
		current->next = new_token;
	}
}

/**
 * Helper function to get the last token from the token list
 *
 * @param head: The head of the token list
 * @return: Pointer to the last token, or NULL if the list is empty
 */
t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
