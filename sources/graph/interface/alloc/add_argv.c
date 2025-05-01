/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:09:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 15:16:31 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "libft.h"

static int	copy_data(char ***new_argv, char **old_argv)
{
	if (!old_argv)
		return (0);
	if (!*new_argv)
		return (-1);
	if (ft_shallow_copy_matrix((void **)*new_argv, (void **)old_argv) == -1)
	{
		free(*new_argv);
		return (-1);
	}
	return (0);
}

// // THIS FUNCTION MIGHT BE FULL COOKED -> GIGA LEAKS IN FUTURE INCOMING
// void	add_argv(t_cmd **cmd, t_parsed_data **data)
// {
// 	char			**new_argv;
// 	unsigned int	len;

// 	len = 1;
// 	new_argv = malloc_double_pointer(len + 1);
// 	new_argv[0] = peek_token(data)->data;
// 	new_argv[1] = NULL;
// 	free((*cmd)->argv);
// 	(*cmd)->argv = new_argv;
// 	advance_token(data);
// 	while (peek_token_label(data) != NULL
// 		&& is_label_argv(peek_token_label(data)))
// 	{
// 		len = ft_len_matrix((const void **)(*cmd)->argv);
// 		if (copy_data(&new_argv, (*cmd)->argv, len) == -1)
// 		{
// 			free((*cmd)->argv);
// 			return ;
// 		}
// 		new_argv[len] = peek_token(data)->data;
// 		new_argv[len + 1] = NULL;
// 		free((*cmd)->argv);
// 		(*cmd)->argv = new_argv;
// 		advance_token(data);
// 	}
// }

static char	**append_to_argv(char **argv, char *new_arg)
{
	unsigned int	len;
	char			**new_argv;

	len = ft_len_matrix((const void **)argv);
	new_argv = malloc_double_pointer(len + 2);
	if (!new_argv)
		return (NULL);
	if (copy_data(&new_argv, argv) == -1)
	{
		free(new_argv);
		return (NULL);
	}
	new_argv[len] = ft_strdup(new_arg);
	new_argv[len + 1] = NULL;
	if (argv != NULL)
		free(argv);
	return (new_argv);
}

char	**process_argument(char **argv, char *arg, int *argv_limit)
{
	int	new_size;

	new_size = ft_strlen(arg) + 1;
	if (new_size > ARG_SIZE)
	{
		argv = append_to_argv(argv, ft_strndup(arg, ARG_SIZE));
		arg += ARG_SIZE;
		(*argv_limit)++;
	}
	argv = append_to_argv(argv, arg);
	if (!argv)
		return (NULL);
	(*argv_limit)++;
	return (argv);
}

void	add_argv(t_cmd **cmd, t_parsed_data **data)
{
	char			**argv;
	int				argv_limit;
	char			*arg;
	t_token_type	*type;

	argv = (*cmd)->argv;
	argv_limit = 0;
	type = peek_token_label(data);
	while (peek_token_label(data) != NULL && is_label_argv(type)
		&& argv_limit < ARG_LIMIT)
	{
		arg = peek_token(data)->data;
		argv = process_argument(argv, arg, &argv_limit);
		if (!argv)
			return ;
		advance_token(data);
		type = peek_token_label(data);
	}
	(*cmd)->argv = argv;
}
