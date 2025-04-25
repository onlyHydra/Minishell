/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:09:52 by schiper           #+#    #+#             */
/*   Updated: 2025/04/25 19:12:06 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_functions.h"
#include "libft.h"

void	add_argv(t_cmd **cmd, t_parsed_data **data)
{
	char	**new_argv;

	while (is_label_argv(peek_token_label(*data)))
	{
		new_argv = malloc_double_pointer(ft_len_matrix((*cmd)->argv) + 2);
		ft_shallow_copy_matrix(new_argv, (*cmd)->argv);
		free((*cmd)->argv);
		(*cmd)->argv = new_argv;
		advance_token(data);
	}
}
