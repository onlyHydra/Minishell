/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:45:31 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 19:34:28 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

void	append_redir(t_redir **list, t_redir *new_redir)
{
	t_redir	*current;

	if (!list || !new_redir)
		return ;
	if (!*list)
	{
		*list = new_redir;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

// syntax error, redir must be followed by filename
void	add_redirection(t_cmd **cmd, t_parsed_data **tokens,
		t_token_type red_type)
{
	t_token_type	type;
	char			*filename;
	t_redir			*redir;
	t_parsed_data	*next_el;

	if (!peek_token_label(tokens))
		return ;
	next_el = *tokens + 1;
	type = *peek_token_label(&next_el);
	filename = peek_token(&next_el)->data;
	redir = allocate_redir(red_type, filename);
	if (!peek_token(tokens) || is_redir_token_type(type)
		|| is_operator_token(type))
		return (free_redir_list((*cmd)->redir_list));
	if (!redir)
		return ;
	append_redir(&(*cmd)->redir_list, redir);
	advance_token(tokens);
	advance_token(tokens);
}
