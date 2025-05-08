/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:26:13 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 20:26:23 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Clean up resources and return NULL
 *
 * @param dir: Directory pointer
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: NULL
 */
char	**cleanup_and_return_null(DIR *dir, char *dir_path, char *file_pattern)
{
	closedir(dir);
	free(dir_path);
	free(file_pattern);
	return (NULL);
}
