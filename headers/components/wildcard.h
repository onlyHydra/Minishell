/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:42:42 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:17:19 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "minishell.h"
#include "models/wildcard_struct.h"
# include <dirent.h>


/* Pattern matching functions */
int					match_pattern(const char *pattern, const char *filename);
int					wildcard_match(const char *pattern, const char *filename);

/* Token expansion functions */
int					expand_wildcard_token(t_token *token);

/* Directory and path handling */
char				**expand_wildcard_in_dir(const char *pattern);
int					split_path_and_pattern(const char *pattern, char **dir_path,
						char **file_pattern);
char				**create_full_paths(char **matches, const char *dir_path);
char				**expand_path_with_wildcard(char *path);
char				**allocate_new_matches(int match_count);

// UTILS
char				**cleanup_and_return_null(DIR *dir, char *dir_path,
						char *file_pattern);

#endif
