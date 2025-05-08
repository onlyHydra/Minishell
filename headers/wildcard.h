/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:42:42 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 20:33:16 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "minishell.h"
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

/* Pattern matching functions */
int					match_pattern(const char *pattern, const char *filename);
int					has_wildcard(char *str_token);
int					wildcard_match(const char *pattern, const char *filename);

/* Context management functions */
t_expand_context	*init_wildcard_expand(const char *pattern);
char				**expand_wildcard_in_current_dir(const char *pattern);

/* Match handling functions */

char				**finalize_wildcard_matches(t_expand_context *context);

/* Token expansion functions */
int					expand_wildcard_token(t_token *token);

/* Directory and path handling */
char				**expand_wildcard_in_dir(const char *pattern);
int					split_path_and_pattern(const char *pattern, char **dir_path,
						char **file_pattern);
char				**create_full_paths(char **matches, const char *dir_path);
char				**expand_path_with_wildcard(char *path);
char				**expand_wildcard_in_dir(const char *pattern);
int					add_wildcard_match(t_expand_context *context,
						const char *filename);
int					init_wildcard_expansion(const char *pattern,
						char **dir_path, char **file_pattern, DIR **dir);
int					process_directory_entries(t_expand_context *context);
t_expand_context	*init_expansion_context(const char *file_pattern, DIR *dir);

// MATCHES UTILS
int					should_include_filename(t_expand_context *context,
						const char *filename);
char				**allocate_new_matches(int match_count);

// UTILS
char				**cleanup_and_return_null(DIR *dir, char *dir_path,
						char *file_pattern);

#endif
