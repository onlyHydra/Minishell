/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:46:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 19:24:40 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Initialize wildcard matches array
 *
 * @param pattern: The wildcard pattern to match against
 * @return: Directory pointer and initialized matches array in a struct
 */
t_expand_context	*init_wildcard_expand(const char *pattern)
{
	t_expand_context	*context;

	context = malloc(sizeof(t_expand_context));
	if (!context)
		return (NULL);
	context->matches = NULL;
	context->match_count = 0;
	context->dir = opendir(".");
	if (!context->dir)
	{
		free(context);
		return (NULL);
	}
	context->pattern = pattern;
	return (context);
}

char	**expand_wildcard_in_dir(const char *pattern)
{
	DIR					*d;
	char				*dir_path;
	char				*file_pattern;
	struct dirent		*entry;
	t_expand_context	*wildcard;

	split_path_and_pattern(pattern, &dir_path, &file_pattern);
	d = opendir(dir_path);
	if (!d)
		return (NULL); // HATE U
	entry = readdir(d);
	while (entry)
	{
		wildcard = init_wildcard_expand(file_pattern);
		if (wildcard_match(wildcard->pattern, entry->d_name))
			add_wildcard_match(wildcard, entry->d_name);
	}
	closedir(d);
	wildcard->matches = finalize_wildcard_matches(wildcard);
	return (create_full_paths(wildcard->matches, dir_path));
}
