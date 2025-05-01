/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:45:31 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 15:29:43 by schiper          ###   ########.fr       */
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
	while (current->filename != NULL && current->type != 0 && current + 1)
		current++;
	*current = *new_redir;
	free(new_redir);
}

void	add_redirection(t_cmd **cmd, t_parsed_data **tokens)
{
	t_token_type	type;
	char			*filename;
	t_redir			*redir;

	if (!peek_token_label(tokens))
		return ;
	type = *peek_token_label(tokens);
	advance_token(tokens);
	if (!peek_token(tokens) || is_operator_token(*tokens))
		return ; // syntax error, redir must be followed by filename
	filename = peek_token(tokens)->data;
	redir = allocate_redir(type, filename);
	if (!redir)
		return ;
	append_redir(&(*cmd)->redir_list, redir);
	advance_token(tokens);
}
