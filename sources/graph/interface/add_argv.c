/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:09:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 02:38:59 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "libft.h"

static int	copy_data(char ***new_argv, char **old_argv, unsigned int len)
{
	*new_argv = malloc_double_pointer(len + 1);
	if (!*new_argv)
		return (-1);
	if (ft_shallow_copy_matrix((void **)*new_argv, (void **)old_argv) == -1)
	{
		free(*new_argv);
		return (-1);
	}
	return (0);
}


// THIS FUNCTION MIGHT BE FULL COOKED -> GIGA LEAKS IN FUTURE INCOMING
void	add_argv(t_cmd **cmd, t_parsed_data **data)
{
	char			**new_argv;
	unsigned int	len;

	len = 1;
	new_argv = malloc_double_pointer(len + 1);
	new_argv[0] = peek_token(data)->data;
	new_argv[1] = NULL;
	free((*cmd)->argv);
	(*cmd)->argv = new_argv;
	advance_token(data);
	while (peek_token_label(data) != NULL
		&& is_label_argv(peek_token_label(data)))
	{
		len = ft_len_matrix((const void **)(*cmd)->argv);
		if (copy_data(&new_argv, (*cmd)->argv, len) == -1)
		{
			free((*cmd)->argv);
			return ;
		}
		new_argv[len] = peek_token(data)->data;
		new_argv[len + 1] = NULL;
		free((*cmd)->argv);
		(*cmd)->argv = new_argv;
		advance_token(data);
	}
}
