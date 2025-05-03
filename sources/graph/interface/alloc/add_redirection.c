/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:45:31 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 22:12:51 by schiper          ###   ########.fr       */
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
void	add_redirection(t_cmd **cmd, t_parsed_data **tokens)
{
	t_token_type	type;
	char			*filename;
	t_redir			*redir;

	if (!peek_token_label(tokens))
		return ;
	advance_token(tokens);
	type = *peek_token_label(tokens);
	if (!peek_token(tokens) || type != FILENAME)
		return (free_redir_list((*cmd)->redir_list));
	filename = peek_token(tokens)->data;
	redir = allocate_redir(type, filename);
	if (!redir)
		return ;
	append_redir(&(*cmd)->redir_list, redir);
	advance_token(tokens);
}
