/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:33:55 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 17:07:17 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models/token_struct.h"

int	is_label_argv(t_token_type type)
{
	return (!is_operator_token(type) && !is_redir_token_type(type));
}

int	is_redir_token_type(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == REDIRECT_APPEND || type == HEREDOC);
}
