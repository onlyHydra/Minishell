/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:29:02 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/21 18:43:02 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_STRUCT_H
# define WILDCARD_STRUCT_H
# include <dirent.h>

/**
 * Structure for wildcard expansion context
 */
typedef struct s_expand_context
{
	char			**matches;
	int				match_count;
	const char		*pattern;
	DIR				*dir;
}					t_expand_context;

t_expand_context	*init_wildcard_expand(const char *pattern);
t_expand_context	*init_expansion_context(const char *file_pattern, DIR *dir);
char				**finalize_wildcard_matches(t_expand_context *context);
int					add_wildcard_match(t_expand_context *context,
						const char *filename);

int					should_include_filename(t_expand_context *context,
						const char *filename);

#endif
